#pragma once
//=====================================================================//
/*!	@file
	@brief	libmad を使った MP3 デコード・クラス @n
			※このクラスを使うには、libmad ライブラリーが必要
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <mad.h>
#include "common/file_io.hpp"
#include "sound/id3_mgr.hpp"
#include "sound/af_play.hpp"
#include "sound/sound_out.hpp"
#include "sound/audio_info.hpp"

extern "C" {
	void set_sample_rate(uint32_t freq);
};

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	MP3 形式デコード・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class mp3_in : public af_play {

		static const uint32_t INPUT_BUFFER_SIZE = 2048;

		mad_stream	mad_stream_;
		mad_frame	mad_frame_;
		mad_synth	mad_synth_;

		uint8_t		input_buffer_[INPUT_BUFFER_SIZE + MAD_BUFFER_GUARD];

		// サブバンド領域フィルター特性用。
		mad_fixed_t		subband_filter_[32];
		bool			subband_filter_enable_;
		bool			id3v1_;

		uint32_t		time_;
		uint32_t		header_size_;

		int fill_read_buffer_(utils::file_io& fin, mad_stream& strm)
 		{
			/* The input bucket must be filled if it becomes empty or if
			 * it's the first execution of the loop.
			 */
			if(strm.buffer == NULL || strm.error == MAD_ERROR_BUFLEN) {
				size_t size;
				size_t remaining;
				unsigned char* ptr;

				/* {2} libmad may not consume all bytes of the input
				 * buffer. If the last frame in the buffer is not wholly
				 * contained by it, then that frame's start is pointed by
				 * the next_frame member of the Stream structure. This
				 * common situation occurs when mad_frame_decode() fails,
				 * sets the stream error code to MAD_ERROR_BUFLEN, and
				 * sets the next_frame pointer to a non NULL value. (See
				 * also the comment marked {4} bellow.)
				 *
				 * When this occurs, the remaining unused bytes must be
				 * put back at the beginning of the buffer and taken in
				 * account before refilling the buffer. This means that
				 * the input buffer must be large enough to hold a whole
				 * frame at the highest observable bit-rate (currently 448
				 * kb/s). XXX=XXX Is 2016 bytes the size of the largest
				 * frame? (448000*(1152/32000))/8
				 */
				if(strm.next_frame != NULL) {
					remaining = strm.bufend - strm.next_frame;
					memmove(&input_buffer_[0], strm.next_frame, remaining);
					ptr  = &input_buffer_[remaining];
					size = INPUT_BUFFER_SIZE - remaining;
				} else {
					size = INPUT_BUFFER_SIZE;
					ptr  = &input_buffer_[0];
					remaining = 0;
				}

				/* Fill-in the buffer. If an error occurs print a message
				 * and leave the decoding loop. If the end of stream is
				 * reached we also leave the loop but the return status is
				 * left untouched.
				 */
				// ReadSize = BstdRead(ReadStart, 1, ReadSize, BstdFile);
				size_t req = size;
				size_t rs = fin.read(ptr, req);
				if(id3v1_) {
					if(fin.tell() >= (fin.get_file_size() - 128)) return -1;
				} else {
					if(fin.eof()) return -1;
				}
				size = rs;
				if(rs < req) {
					memset(&ptr[rs], 0, MAD_BUFFER_GUARD);
					size += MAD_BUFFER_GUARD;
				}

				/* Pipe the new buffer content to libmad's stream decoder
				 * facility.
				 */
				mad_stream_buffer(&strm, &input_buffer_[0], size + remaining);
				strm.error = MAD_ERROR_NONE;
				return 0;
			} else {
				return 1;
			}
		}


		/****************************************************************************
		 * Applies a frequency-domain filter to audio data in the subband-domain.	*
		 ****************************************************************************/
		void apply_filter_(mad_frame& frame)
		{
			/* There is two application loops, each optimized for the number
			 * of audio channels to process. The first alternative is for
			 * two-channel frames, the second is for mono-audio.
			 */
			int num = MAD_NSBSAMPLES(&frame.header);
			if(frame.header.mode != MAD_MODE_SINGLE_CHANNEL) {
				for(int ch = 0; ch < 2; ++ch) {
					for(int s = 0; s < num; ++s) {
						for(int sb = 0; sb < 32; ++sb) {
							frame.sbsample[ch][s][sb] =
								mad_f_mul(frame.sbsample[ch][s][sb], subband_filter_[sb]);
						}
					}
				}
			} else {
				for(int s = 0; s < num; ++s) {
					for(int sb = 0; sb < 32; ++sb) {
						frame.sbsample[0][s][sb] =
							mad_f_mul(frame.sbsample[0][s][sb], subband_filter_[sb]);
					}
				}
			}
		}


		static const short SHRT_MAX_ = 32767;

		/****************************************************************************
		 * Converts a sample from mad's fixed point number format to a signed		*
		 * short (16 bits).															*
		 ****************************************************************************/
		static short MadFixedToSshort(mad_fixed_t v)
		{
			/* A fixed point number is formed of the following bit pattern:
			 *
			 * SWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFF
			 * MSB                          LSB
			 * S ==> Sign (0 is positive, 1 is negative)
			 * W ==> Whole part bits
			 * F ==> Fractional part bits
			 *
			 * This pattern contains MAD_F_FRACBITS fractional bits, one
			 * should alway use this macro when working on the bits of a fixed
			 * point number. It is not guaranteed to be constant over the
			 * different platforms supported by libmad.
			 *
			 * The signed short value is formed, after clipping, by the least
			 * significant whole part bit, followed by the 15 most significant
			 * fractional part bits. Warning: this is a quick and dirty way to
			 * compute the 16-bit number, madplay includes much better
			 * algorithms.
			 */

			// Clipping..
			if(v >= MAD_F_ONE) {
				return SHRT_MAX_;
			}
			if(v <= -MAD_F_ONE) {
				return -SHRT_MAX_;
			}

			return (signed short)(v >> (MAD_F_FRACBITS - 15));
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		mp3_in() : subband_filter_enable_(false), id3v1_(false), time_(0), header_size_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	情報を取得 @n
					可変ビットレートの場合は、情報は正確では無い。@n
					※全体時間は正確
			@param[in]	fin		file_io コンテキスト（参照）
			@param[out]	info	情報
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool info(utils::file_io& fin, audio_info& info) noexcept
		{
			id3_mgr id3;
			set_state(STATE::TAG);
			if(!id3.parse(fin)) {
				set_state(STATE::IDLE);
				return false;
			}

			if(tag_task_) {
				const auto& tag = id3.get_tag();
				tag_task_(fin, tag);
			}

			mad_stream_init(&mad_stream_);
			mad_header_init(&mad_frame_.header);

			uint32_t forg = fin.tell();
			info.header_size = forg;
			header_size_ = forg;

			// 全体のフレーム数をカウント
			uint32_t frames = 0;
			uint32_t freq = 0;
			while(fill_read_buffer_(fin, mad_stream_) >= 0) {
				if(fin.get_error()) {
					break;
				}
				if(mad_header_decode(&mad_frame_.header, &mad_stream_) != 0) {
					if(MAD_RECOVERABLE(mad_stream_.error)) {
						continue;
					} else {
						if(mad_stream_.error == MAD_ERROR_BUFLEN) {
							continue;
						} else {
							break;
						}
					}
				}
				++frames;
				if(freq < mad_frame_.header.samplerate) {
					freq = mad_frame_.header.samplerate;
				}
			}
			fin.seek(utils::file_io::SEEK::SET, forg);

			info.samples = frames * 1152;
			if(mad_frame_.header.mode != MAD_MODE_SINGLE_CHANNEL) {
				info.type = audio_format::PCM16_STEREO;
				info.chanels = 2;
			} else {
				info.type = audio_format::PCM16_MONO;
				info.chanels = 1;
			}
			info.bits = 16;
			info.frequency = freq;
			info.total_second = info.samples / freq;

			mad_header_finish(&mad_frame_.header);
			mad_frame_finish(&mad_frame_);

			set_state(STATE::IDLE);

			if(info.frequency > 0) {
				set_sample_rate(info.frequency);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デコード @n
					デコードの準備として、info で情報を取得する必要がある。
			@param[in]	fin		file_io コンテキスト（参照）
			@param[in]	out		オーディオ出力（参照）
			@return 正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		template <class SOUND_OUT>
		bool decode(utils::file_io& fin, SOUND_OUT& out)
		{
			mad_stream_init(&mad_stream_);
			mad_frame_init(&mad_frame_);
			mad_synth_init(&mad_synth_);
///			mad_timer_reset(&mad_timer_);

			uint32_t forg = fin.seek(utils::file_io::SEEK::SET, header_size_);

			uint32_t pos = 0;
			uint32_t frame_count = 0;
			bool status = true;
			bool pause = false;
			set_state(STATE::PLAY);
			while(fill_read_buffer_(fin, mad_stream_) >= 0) {

				if(fin.get_error()) {
					break;
				}

				CTRL ctrl = CTRL::NONE;
				if(ctrl_task_) {
					ctrl = ctrl_task_();
				}
				if(ctrl == CTRL::NEXT) {
					out.mute();
					status = true;
					break;
				} else if(ctrl == CTRL::STOP) {
					out.mute();
					status = false;
					break;
				} else if(ctrl == CTRL::REPLAY) {
					out.mute();
					fin.seek(utils::file_io::SEEK::SET, forg);
					pos = 0;
					time_ = 0;
					frame_count = 0;
					status = true;
					pause = false;
					continue;
				} else if(ctrl == CTRL::PAUSE) {
					out.mute();
					pause = !pause;
				}
				if(pause) {
					set_state(STATE::PAUSE);
					system_delay(5);
					continue;
				} else {
					set_state(STATE::PLAY);
				}

				if(mad_frame_decode(&mad_frame_, &mad_stream_)) {
					if(MAD_RECOVERABLE(mad_stream_.error)) {
						continue;
					} else {
						if(mad_stream_.error == MAD_ERROR_BUFLEN) {
							continue;
						} else {
							status = false;
							break;
						}
					}
				}

				frame_count++;
///				mad_timer_add(&mad_timer_, mad_frame_.header.duration);

				if(subband_filter_enable_) {
					apply_filter_(mad_frame_);
				}

				mad_synth_frame(&mad_synth_, &mad_frame_);

				// 1152 sample / frame
				for(uint32_t i = 0; i < mad_synth_.pcm.length; ++i) {
					while((out.at_fifo().size() - out.at_fifo().length()) < 64) {
						system_delay(1);
					}
					typename SOUND_OUT::WAVE t;
					if(MAD_NCHANNELS(&mad_frame_.header) == 1) {
						t.l_ch = t.r_ch = MadFixedToSshort(mad_synth_.pcm.samples[0][i]);
					} else {
						t.l_ch = MadFixedToSshort(mad_synth_.pcm.samples[0][i]);
						t.r_ch = MadFixedToSshort(mad_synth_.pcm.samples[1][i]);
					}
					out.at_fifo().put(t);
					++pos;
				}

				{
					uint32_t s = pos / mad_frame_.header.samplerate;
					if(s != time_) {
						if(update_task_) {
							update_task_(s);
						}
						time_ = s;
					}
				}
			}
			set_state(STATE::IDLE);

			mad_synth_finish(&mad_synth_);
			mad_frame_finish(&mad_frame_);
			mad_stream_finish(&mad_stream_);

			return status;
		}
	};
}
