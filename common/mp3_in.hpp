#pragma once
//=====================================================================//
/*!	@file
	@brief	MP3 ファイルを扱うクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RL78/blob/master/LICENSE
*/
//=====================================================================//
#include <mad.h>

namespace audio {

	//-----------------------------------------------------------------//
	/*!
		@brief	MP3 形式ファイルクラス
	*/
	//-----------------------------------------------------------------//
	class mp3_in {

		mad_stream	mad_stream_;
		mad_frame	mad_frame_;
		mad_synth	mad_synth_;
		mad_timer_t	mad_timer_;

	public:

		void test()
		{
			mad_stream_init(&mad_stream_);
			mad_frame_init(&mad_frame_);
			mad_synth_init(&mad_synth_);
			mad_timer_reset(&mad_timer_);


			mad_frame_decode(&mad_frame_, &mad_stream_);
		}

#if 0
		bool decode_(file_io& fin, audio out)
		{
			mad_stream_init(&mad_stream_);
			mad_frame_init(&mad_frame_);
			mad_synth_init(&mad_synth_);
			mad_timer_reset(&mad_timer_);

			int pos = 0;
			int frame_count = 0;
			bool status = true;
			while(fill_read_buffer_(fin, mad_stream_) >= 0) {

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
				mad_timer_add(&mad_timer_, mad_frame_.header.duration);

				if(subband_filter_enable_) {
					apply_filter_(mad_frame_);
				}

				mad_synth_frame(&mad_synth_, &mad_frame_);

				for(int i = 0; i < mad_synth_.pcm.length; ++i) {
					if(MAD_NCHANNELS(&mad_frame_.header) == 1) {
						pcm16_m pcm;
						pcm.w = MadFixedToSshort(mad_synth_.pcm.samples[0][i]);
						out->put(pos, pcm);
					} else {
						pcm16_s pcm;
						pcm.l = MadFixedToSshort(mad_synth_.pcm.samples[0][i]);
						pcm.r = MadFixedToSshort(mad_synth_.pcm.samples[1][i]);
						out->put(pos, pcm);
					}
					++pos;
				}
			}

			mad_synth_finish(&mad_synth_);
			mad_frame_finish(&mad_frame_);
			mad_stream_finish(&mad_stream_);

			return status;
		}
#endif
	};
}

