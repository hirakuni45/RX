#pragma once
//=====================================================================//
/*!	@file
	@brief	BMP 画像ファイルを扱うクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/file_io.hpp"
#include "common/vtx.hpp"
#include "graphics/img.hpp"

namespace img {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	BMP 形式ファイルクラス
		@param[in]	PLOT	描画ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PLOT>
	class bmp_in {

		PLOT&		plot_;

		static const uint16_t BMP_SIGNATURE		 = 0x4D42;
		static const uint16_t BMP_SIG_BYTES		 = 2;

		// BITMAPFILEHEADER
		static const uint16_t BFH_WTYPE			 = 0;	// WORD   bfType;
		static const uint16_t BFH_DSIZE			 = 2;	// DWORD  bfSize;
		static const uint16_t BFH_WRESERVED1	 = 6;	// WORD   bfReserved1;
		static const uint16_t BFH_WRESERVED2     = 8;	// WORD   bfReserved2;
		static const uint16_t BFH_DOFFBITS		 = 10;	// DWORD  bfOffBits;
		static const uint16_t BFH_DBIHSIZE		 = 14;	// DWORD  biSize;
		static const uint16_t FILEHED_SIZE		 = 14;	// sizeof(BITMAPFILEHEADER)
		static const uint16_t BIHSIZE_SIZE		 = 4;	// sizeof(biSize)

		// BITMAPINFOHEADER, BITMAPV4HEADER, BITMAPV5HEADER
		static const uint16_t BIH_DSIZE			 = 0;	// DWORD  biSize;
		static const uint16_t BIH_LWIDTH		 = 4;	// LONG   biWidth;
		static const uint16_t BIH_LHEIGHT		 = 8;	// LONG   biHeight;
		static const uint16_t BIH_WPLANES		 = 12;	// WORD   biPlanes;
		static const uint16_t BIH_WBITCOUNT		 = 14;	// WORD   biBitCount;
		static const uint16_t BIH_DCOMPRESSION	 = 16;	// DWORD  biCompression;
		static const uint16_t BIH_DSIZEIMAGE	 = 20;	// DWORD  biSizeImage;
		static const uint16_t BIH_LXPELSPERMETER = 24;	// LONG   biXPelsPerMeter;
		static const uint16_t BIH_LYPELSPERMETER = 28;	// LONG   biYPelsPerMeter;
		static const uint16_t BIH_DCLRUSED		 = 32;	// DWORD  biClrUsed;
		static const uint16_t BIH_DCLRIMPORANT	 = 36;	// DWORD  biClrImportant;
		static const uint16_t B4H_DREDMASK		 = 40; 	// DWORD  bV4RedMask;
		static const uint16_t B4H_DGREENMASK	 = 44;	// DWORD  bV4GreenMask;
		static const uint16_t B4H_DBLUEMASK		 = 48;	// DWORD  bV4BlueMask;
		static const uint16_t B4H_DALPHAMASK	 = 52;	// DWORD  bV4AlphaMask;
		static const uint16_t B4H_DCSTYPE		 = 56;	// DWORD  bV4CSType;
		static const uint16_t B4H_XENDPOINTS	 = 60;	// CIEXYZTRIPLE bV4Endpoints;
		static const uint16_t B4H_DGAMMARED		 = 96;	// DWORD  bV4GammaRed;
		static const uint16_t B4H_DGAMMAGREEN	 = 100;	// DWORD  bV4GammaGreen;
		static const uint16_t B4H_DGAMMABLUE	 = 104;	// DWORD  bV4GammaBlue;
		static const uint16_t B5H_DINTENT		 = 108;	// DWORD  bV5Intent;
		static const uint16_t B5H_DPROFILEDATA	 = 112;	// DWORD  bV5ProfileData;
		static const uint16_t B5H_DPROFILESIZE	 = 116;	// DWORD  bV5ProfileSize;
		static const uint16_t B5H_DRESERVED		 = 120;	// DWORD  bV5Reserved;
		static const uint16_t INFOHED_SIZE		 = 40;	// sizeof(BITMAPINFOHEADER)
		static const uint16_t BMPV4HED_SIZE		 = 108;	// sizeof(BITMAPV4HEADER)
		static const uint16_t BMPV5HED_SIZE		 = 124;	// sizeof(BITMAPV5HEADER)

		// BITMAPCOREHEADER
		static const uint16_t BCH_DSIZE			 = 0;	// DWORD  bcSize;
		static const uint16_t BCH_WWIDTH		 = 4;	// WORD   bcWidth;
		static const uint16_t BCH_WHEIGHT		 = 6;	// WORD   bcHeight;
		static const uint16_t BCH_WPLANES		 = 8;	// WORD   bcPlanes;
		static const uint16_t BCH_WBITCOUNT		 = 10;	// WORD   bcBitCount;
		static const uint16_t COREHED_SIZE		 = 12;	// sizeof(BITMAPCOREHEADER)

		// RGBQUAD
		static const uint16_t RGBQ_BLUE			 = 0;	// BYTE   rgbBlue;
		static const uint16_t RGBQ_GREEN		 = 1;	// BYTE   rgbGreen;
		static const uint16_t RGBQ_RED			 = 2;	// BYTE   rgbRed;
		static const uint16_t RGBQ_RESERVED		 = 3;	// BYTE   rgbReserved;
		static const uint16_t RGBQUAD_SIZE		 = 4;	// sizeof(RGBQUAD)

		// RGBTRIPLE
		static const uint16_t RGBT_BLUE			 = 0;	// BYTE   rgbtBlue;
		static const uint16_t RGBT_GREEN		 = 1;	// BYTE   rgbtGreen;
		static const uint16_t RGBT_RED			 = 2;	// BYTE   rgbtRed;
		static const uint16_t RGBTRIPLE_SIZE	 = 3;	// sizeof(RGBTRIPLE)


		/* Constants for the biCompression field */
		static const uint16_t BI_RGB			 = 0;	// Uncompressed
		static const uint16_t BI_RLE8			 = 1;	// RLE (8 bits/pixel)
		static const uint16_t BI_RLE4			 = 2;	// RLE (4 bits/pixel)
		static const uint16_t BI_BITFIELDS		 = 3;	// Bitfield
		static const uint16_t BI_JPEG			 = 4;	// JPEG Extension
		static const uint16_t BI_PNG			 = 5;	// PNG Extension

		static const uint16_t BMP_MAX_WIDTH      = 16384;  // 許容される最大サイズ
		static const uint16_t BMP_MAX_HEIGHT	 = 16384;  // 許容される最大サイズ

		struct BGRA_PAD {
			unsigned int	b;
			unsigned int	g;
			unsigned int	r;
			unsigned int	a;
		};

		struct bmp_info {
			int			offbits;
			int			bihsize;
			int			skip;
			int			width;
			int			height;
			int			depth;
			int			compression;
			int			palette_size;

			BGRA_PAD	color_mask;
			bool		topdown;
			bool		alpha_chanel;
		};

		uint32_t	prgl_ref_;
		uint32_t	prgl_pos_;

		uint8_t		rgbq_[RGBQUAD_SIZE];


		void render_idx_(int16_t x, int16_t y, uint8_t idx)
		{
			auto i = idx * RGBQUAD_SIZE;
			uint8_t r = rgbq_[i + RGBT_RED];
			uint8_t g = rgbq_[i + RGBT_GREEN];
			uint8_t b = rgbq_[i + RGBT_BLUE];
			plot_(x, y, r, g, b);
		}


		/*----------------------------------------------------------/
		/	メモリから little-endien 形式 4バイト無符号整数を読む	/
		/----------------------------------------------------------*/
		static unsigned int mgetdwl_(unsigned char *p)
		{
			return ((unsigned int)p[0]      ) + ((unsigned int)p[1] <<  8) +
			       ((unsigned int)p[2] << 16) + ((unsigned int)p[3] << 24);
		}


		/*----------------------------------------------------------/
		/	メモリから little-endien 形式 2バイト無符号整数を読む	/
		/----------------------------------------------------------*/
		static unsigned int mgetwl_(unsigned char *p)
		{
			return ((unsigned int)p[0]) + ((unsigned int)p[1] << 8);
		}


		/*----------------------------------------------------------/
		/	bmp ファイルヘッダーのみ展開して、情報を得る			/
		/----------------------------------------------------------*/
		static bool read_header_bmp_(utils::file_io& fin, bmp_info& bmp)
		{
			uint8_t bfh[FILEHED_SIZE + BMPV5HED_SIZE];
			uint8_t *const bih = bfh + FILEHED_SIZE;

			// skip MAC-Binary header がある場合を考えてヘッダーを特定
			for(int i = 0; i < 512; i++) {
				if(fin.read(bfh, (FILEHED_SIZE + BIHSIZE_SIZE), 1) != 1) {
					return false;
				}
				if(mgetwl_(bfh + BFH_WTYPE) == BMP_SIGNATURE) break;
				if(i != 0) {
					return false;
				}
				if(fin.read(bfh, (128 - FILEHED_SIZE - BIHSIZE_SIZE), 1) != 1) {
					return false;
				}
			}

			bmp.offbits = mgetdwl_(bfh + BFH_DOFFBITS);
			bmp.bihsize = mgetdwl_(bfh + BFH_DBIHSIZE);
			bmp.skip    = bmp.offbits - bmp.bihsize - FILEHED_SIZE;

			if(bmp.bihsize < COREHED_SIZE || bmp.bihsize > BMPV5HED_SIZE
				|| bmp.offbits < (bmp.bihsize + FILEHED_SIZE)) {
				return false;
			}

			if(fin.read((bih + BIHSIZE_SIZE), (bmp.bihsize - BIHSIZE_SIZE), 1) != 1) {
				return false;
			}

			bmp.topdown = false;
			if(bmp.bihsize >= INFOHED_SIZE) {
				// [Windows] style BMP
				bmp.width  = mgetdwl_(bih + BIH_LWIDTH);
				bmp.height = mgetdwl_(bih + BIH_LHEIGHT);
				bmp.depth  = mgetwl_(bih + BIH_WBITCOUNT);
				bmp.compression   = mgetdwl_(bih + BIH_DCOMPRESSION);
				bmp.palette_size  = RGBQUAD_SIZE;
				if(static_cast<int>(bmp.height) < 0) {
					bmp.height  = -static_cast<int>(bmp.height);
					bmp.topdown = true;
				}
			} else {
			// [OS/2] style BMP
				bmp.width  = mgetwl_(bih + BCH_WWIDTH);
				bmp.height = mgetwl_(bih + BCH_WHEIGHT);
				bmp.depth  = mgetwl_(bih + BCH_WBITCOUNT);
				bmp.compression   = BI_RGB;
				bmp.palette_size  = RGBTRIPLE_SIZE;
			}

			if(bmp.width  <= 0 || bmp.width >= BMP_MAX_WIDTH) {
				return false;
			}
			if(bmp.height <= 0 || bmp.height >= BMP_MAX_HEIGHT) {
				return false;
			}

			bmp.alpha_chanel = false;

			switch(bmp.compression) {
			case BI_RGB:
				if(bmp.depth != 1 && bmp.depth != 4 && bmp.depth != 8
					&& bmp.depth != 16 && bmp.depth != 24 && bmp.depth != 32) {
					return false;
				}

			// RGB565 16bits color
				if(bmp.depth == 16) {
					bmp.color_mask.a = 0x0000;
					bmp.color_mask.r = 0x7C00;
					bmp.color_mask.g = 0x03E0;
					bmp.color_mask.b = 0x001F;
					bmp.compression  = BI_BITFIELDS;
				}
			break;

			case BI_BITFIELDS:
				if(bmp.depth != 16 && bmp.depth != 32) {
					return false;
				}
				if(bmp.bihsize < INFOHED_SIZE + 12) {
					if(bmp.skip < (INFOHED_SIZE + 12 - bmp.bihsize)) {
						return false;
					}
					if(fin.read((bih + bmp.bihsize), (INFOHED_SIZE + 12 - bmp.bihsize), 1) != 1) {
						return false;
					}
					bmp.skip -= (INFOHED_SIZE + 12 - bmp.bihsize);
				}
				bmp.color_mask.a = 0x00000000;
				bmp.color_mask.r = mgetdwl_(bih + B4H_DREDMASK);
				bmp.color_mask.g = mgetdwl_(bih + B4H_DGREENMASK);
				bmp.color_mask.b = mgetdwl_(bih + B4H_DBLUEMASK);

				if(bmp.depth == 32 && bmp.bihsize >= (INFOHED_SIZE + 16)) {
					bmp.color_mask.a = mgetdwl_(bih + B4H_DALPHAMASK);
					if(bmp.color_mask.a != 0) {
						bmp.alpha_chanel = true;
					}
				}

				if(bmp.depth == 32 && bmp.color_mask.b == 0x000000FF &&
				    bmp.color_mask.g == 0x0000FF00 && bmp.color_mask.r == 0x00FF0000 &&
				    (bmp.color_mask.a == 0xFF000000 || bmp.color_mask.a == 0x00000000)) {
					bmp.compression = BI_RGB;
				}
				break;

			case BI_RLE8:
				if(bmp.depth != 8) {
					return false;
				}
				break;

			case BI_RLE4:
				if(bmp.depth != 4) {
					return false;
				}
				break;

			default:
				return false;
			}
			return true;
		}


		/*----------------------------------------------------------------------/
		/	インデックス・カラー(無圧縮 1, 4, 8 ビット) 形式の画像データを展開	/
		/----------------------------------------------------------------------*/
		bool read_idx_(utils::file_io& fin, const bmp_info& bmp)
		{
			size_t stride = bmp.width * bmp.depth;
			if(stride & 7) stride += 8;
			stride >>= 3;
			if(stride & 3) stride += 4 - (stride & 3);

			char tmp[stride];
			char* buf = tmp;
			short d;
			vtx::spos pos;
			if(bmp.topdown) {
				pos.y = 0;
				d = 1;
			} else {
				pos.y = bmp.height - 1;
				d = -1;
			}
			for(int h = 0; h < bmp.height; ++h) {
				if(fin.read(buf, 1, stride) != stride) {
					return false;
				}
				int depth = 0;
				for(pos.x = 0; pos.x < bmp.width; ++pos.x) {
					unsigned char idx = buf[depth / 8];
					if(bmp.depth == 4) {
						if(~pos.x & 1) idx >>= 4;
						idx &= 15;
					} else if(bmp.depth == 1) {
						idx >>= (~pos.x & 3);
						idx &= 1;
					}
					depth += bmp.depth;
					render_idx_(pos.x, pos.y, idx);
				}
				pos.y += d;
				++prgl_pos_;
			}
			return true;
		}


		/*------------------------------------------------------/
		/	BGR (無圧縮 24/32 ビット) 形式の画像データを展開	/
		/------------------------------------------------------*/
		bool read_rgb_(utils::file_io& fin, const bmp_info& bmp)
		{
			int pads = bmp.depth / 8;
			size_t stride = bmp.width * pads;
			if(stride & 3) stride += 4 - (stride & 3);

			char tmp[stride];
			char* buf = tmp;
			short d;
			vtx::spos pos;
			if(bmp.topdown) {
				pos.y = 0;
				d = 1;
			} else {
				pos.y = bmp.height - 1;
				d = -1;
			}
			for(int h = 0; h < bmp.height; ++h) {
				if(fin.read(buf, 1, stride) != stride) {
					return false;
				}
				char* src = buf;
				for(pos.x = 0; pos.x < bmp.width; ++pos.x) {
					auto r = src[2];
					auto g = src[1];
					auto b = src[0];
					plot_(pos.x, pos.y, r, g, b);
					src += pads;
				}
				pos.y += d;
				++prgl_pos_;
			}
			return true;
		}


		/*----------------------------------------------/
		/	ビットマスクからシフトする回数を得る		/
		/----------------------------------------------*/
		static int shift_count(unsigned int mask)
		{
			int cnt = 0;
			while(mask != 0) {
				mask >>= 1;
				cnt++;
			}
			return cnt;
		}


		/*----------------------------------------------/
		/	ビット数を数える							/
		/----------------------------------------------*/
		static int bits_count(unsigned int bits)
		{
			int cnt = 0;
			for(int i = 0; i < 32; ++i) {
				if(bits & 1) cnt++;
				bits >>= 1;
				if(bits == 0) break;
			}
			return cnt;
		}


		/*----------------------------------------------/
		/	BI_BITFIELDS 形式の画像データを展開			/
		/----------------------------------------------*/
		bool read_bitfield_(utils::file_io& fin, const bmp_info& bmp)
		{
			volatile BGRA_PAD shift_cnt;
			volatile BGRA_PAD bits_cnt;
			if(bmp.depth == 16) {
				shift_cnt.r = shift_count(bmp.color_mask.r);
				bits_cnt.r  = bits_count(bmp.color_mask.r);
				shift_cnt.g = shift_count(bmp.color_mask.g);
				bits_cnt.g  = bits_count(bmp.color_mask.g);
				shift_cnt.b = shift_count(bmp.color_mask.b);
				bits_cnt.b  = bits_count(bmp.color_mask.b);
				shift_cnt.a = shift_count(bmp.color_mask.a);
				bits_cnt.a  = bits_count(bmp.color_mask.a);

//				boost::format("mask: %x, %x, %x, %x\n")
//					% bmp.color_mask.r % bmp.color_mask.g % bmp.color_mask.b % bmp.color_mask.a;
//				boost::format("Shift: %d, %d, %d, %d\n") % shift_cnt.r % shift_cnt.g % shift_cnt.b % shift_cnt.a;
//				boost::format("Bits: %d, %d, %d, %d\n") % bits_cnt.r % bits_cnt.g % bits_cnt.b % bits_cnt.a;
			}

			size_t stride = (bmp.width * (bmp.depth / 8) + 3) & (~3);

			char tmp[stride];
			char* rowb = tmp;
			vtx::spos pos;
			short d;
			if(bmp.topdown) {
				pos.y = 0;
				d = 1;
			} else {
				pos.y = bmp.height - 1;
				d = -1;
			}
			for(int h = 0; h < bmp.height; ++h) {
				if(fin.read(rowb, 1, stride) != stride) {
					return false;
				}

				char* src = rowb;
				switch(bmp.depth) {
				case 16:
					for(pos.x = 0; pos.x < bmp.width; ++pos.x) {
						unsigned int v = *(unsigned char *)src++;
						v |= ( *(unsigned char *)src++ ) << 8;
						uint16_t r = (v & bmp.color_mask.r) >> (shift_cnt.r - bits_cnt.r);
						uint16_t g = (v & bmp.color_mask.g) >> (shift_cnt.g - bits_cnt.g);
						uint16_t b = (v & bmp.color_mask.b) >> (shift_cnt.b - bits_cnt.b);
						r = (r << (8 - bits_cnt.r)) | (r >> (8 - bits_cnt.r));
						g = (g << (8 - bits_cnt.g)) | (g >> (8 - bits_cnt.g));
						b = (b << (8 - bits_cnt.b)) | (b >> (8 - bits_cnt.b));
						plot_(pos.x, pos.y, r, g, b);
					}
					break;

				case 32:
					for(pos.x = 0; pos.x < bmp.width; ++pos.x) {
						auto r = src[2];
						auto g = src[1];
						auto b = src[0];
						auto a = src[3];
						src += 4;
						plot_(pos.x, pos.y, r, g, b);
					}
					break;
				}
				pos.y += d;
				++prgl_pos_;
			}

			return true;
		}


		/*----------------------------------------------/
		/	BI_RLE8 / BI_RLE4 形式の画像データを展開	/
		/----------------------------------------------*/
		bool decompress_rle_(utils::file_io& fin, const bmp_info& bmp)
		{
			size_t stride = bmp.width * bmp.depth;
			if(stride & 7) stride += 8;
			stride >>= 3;
			if(stride & 3) stride += 4 - (stride & 3);

			vtx::spos pos;
			short dy;
			pos.x = 0;
			if(bmp.topdown) {
				pos.y = 0;
				dy = 1;
			} else {
				pos.y = bmp.height - 1;
				dy = -1;
			}
			unsigned char buf[258 * 4];		/* 258 or above */
			unsigned char* bfptr = buf;
			size_t bfcnt = 0;
			for( ; ; ) {
				unsigned int reclen;
				while(bfcnt < (reclen = 2) || (bfptr[0] == 0 && (
					 (bfptr[1] == 2 && bfcnt < (reclen += 2)) || (bfptr[1] >= 3 &&
					  bfcnt < (reclen += (bfptr[1] * bmp.depth + 15) / 16 * 2))))) {
					if(bfptr != buf && bfcnt != 0) memmove(buf, bfptr, bfcnt);
					size_t rd = fin.read(buf + bfcnt, 1, sizeof(buf) - bfcnt);
					if(rd == 0) {
						if(pos.x >= bmp.width) {
							pos.y += dy;
							++prgl_pos_;
						}
						if(pos.y >= bmp.height) return false;	/* missing EoB marker */
						else return false;	// ferror(fp) ? err_false : err_readeof;
					}
					bfptr  = buf;
					bfcnt += rd;
				}
				if(pos.y >= bmp.height) {
					/* We simply discard the remaining records */
					if(bfptr[0] == 0 && bfptr[1] == 1) break;	/* EoB marker */
					bfptr += reclen;
					bfcnt -= reclen;
					continue;
				}
				if(bfptr[0] != 0) {				/* Encoded-mode record */
					int n = bfptr[0];
					uint8_t c = bfptr[1];
					switch(bmp.depth) {
					case 8:						/* BI_RLE8 */
						while(n > 0 && pos.x < bmp.width) {
							render_idx_(pos.x, pos.y, c);
							--n;
							++pos.x;
						}
						break;
					case 4:						/* BI_RLE4 */
						int o = 0;
						uint8_t c0 = c >> 4;
						uint8_t c1 = c & 0xf;
						while(n > 0 && pos.x < bmp.width) {
							if(o & 1) render_idx_(pos.x, pos.y, c1);
							else render_idx_(pos.x, pos.y, c0);
							--n;
							++pos.x;
							++o;
						}
						break;
					}
				} else if (bfptr[1] >= 3) {			/* Absolute-mode record */
					int n = bfptr[1];
					unsigned char* p = bfptr + 2;
					switch(bmp.depth) {
					case 8:						/* BI_RLE8 */
						while(n > 0 && pos.x < bmp.width) {
							uint8_t c = *p++;
							render_idx_(pos.x, pos.y, c);
							--n;
							++pos.x;
						}
						break;
					case 4:						/* BI_RLE4 */
						int o = 0;
						while(n > 0 && pos.x < bmp.width) {
							uint8_t c0 = p[o >> 1] >> 4;
							uint8_t c1 = p[o >> 1] & 0xf;
							if(o & 1) render_idx_(pos.x, pos.y, c1);
							else render_idx_(pos.x, pos.y, c0);
							--n;
							++pos.x;
							++o;
						}
						break;
					}
				} else if (bfptr[1] == 2) {			/* Delta record */
					pos.x += bfptr[2];
					pos.y += bfptr[3] * dy;
					prgl_pos_ += bfptr[3];
				} else if (bfptr[1] == 0) {			/* End of line marker */
					pos.x = 0;
					pos.y += dy;
					++prgl_pos_;
				} else /*if (bfptr[1] == 1)*/ {		/* End of bitmap marker */
					break;
				}
				bfptr += reclen;
				bfcnt -= reclen;
			}

			return true;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	plot	描画ファンクタ
		*/
		//-----------------------------------------------------------------//
		bmp_in(PLOT& plot) noexcept : plot_(plot), prgl_ref_(0), prgl_pos_(0),
			rgbq_{ 0 } { }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル拡張子を返す
			@return ファイル拡張子の文字列
		*/
		//-----------------------------------------------------------------//
		const char* get_file_ext() const noexcept { return "bmp"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	BMP ファイルか確認する
			@param[in]	fin	file_io クラス
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(utils::file_io& fin) noexcept
		{
			bmp_info bmp;
			long pos = fin.tell();
			bool ret = read_header_bmp_(fin, bmp);
			fin.seek(utils::file_io::SEEK::SET, pos);
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	画像ファイルの情報を取得する
			@param[in]	fin	file_io クラス
			@param[in]	fo	情報を受け取る構造体
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool info(utils::file_io& fin, img::img_info& fo) noexcept
		{
			long pos = fin.tell();

			bmp_info bmp;
			if(!read_header_bmp_(fin, bmp)) {
				return false;
			}

			fin.seek(utils::file_io::SEEK::SET, pos);

			fo.width  = bmp.width;
			fo.height = bmp.height;
//			fo.mipmap_level = 0;
//			fo.multi_level = 0;
			fo.grayscale = false;

			if(bmp.depth <= 8) {
				fo.i_depth = 8;
				fo.r_depth = 8;
				fo.g_depth = 8;
				fo.b_depth = 8;
				fo.a_depth = 0;
				fo.clut_num = 1 << bmp.depth;
			} else if(bmp.depth == 16) {
				fo.i_depth = 0;
				fo.r_depth = 5;
				fo.g_depth = 6;
				fo.b_depth = 5;
				fo.a_depth = 0;
				fo.clut_num = 0;
			} else if(bmp.depth == 24) {
				fo.i_depth = 0;
				fo.r_depth = 8;
				fo.g_depth = 8;
				fo.b_depth = 8;
				fo.a_depth = 0;
				fo.clut_num = 0;
			} else if(bmp.depth == 32) {
				fo.i_depth = 0;
				fo.r_depth = 8;
				fo.g_depth = 8;
				fo.b_depth = 8;
				fo.a_depth = 8;
				fo.clut_num = 0;
			} else {
				fo.i_depth = 0;
				fo.r_depth = 0;
				fo.g_depth = 0;
				fo.b_depth = 0;
				fo.a_depth = 0;
				fo.clut_num = 0;
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	BMP ファイルをロードする
			@param[in]	fin	ファイル I/O クラス
			@param[in]	opt	フォーマット固有の設定文字列
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool load(utils::file_io& fin, const char* opt = nullptr) noexcept
		{
			long pos = fin.tell();
			bmp_info bmp;
			if(!read_header_bmp_(fin, bmp)) {
				fin.seek(utils::file_io::SEEK::SET, pos);
				return false;
			}

			if(bmp.depth <= 8) {
///				img_ = shared_img(new img_idx8);
///				img_->create(vtx::spos(bmp.width, bmp.height));
			} else {
///				img_ = shared_img(new img_rgba8);
///				img_->create(vtx::spos(bmp.width, bmp.height), bmp.alpha_chanel);
			}

			prgl_pos_ = 0;
			prgl_ref_ = bmp.height;

			uint32_t clutnum = 0;
			if(bmp.depth <= 8) {
				if(bmp.skip >= bmp.palette_size << bmp.depth) {
					clutnum = 1 << bmp.depth;
					bmp.skip -= bmp.palette_size << bmp.depth;
				} else {
					clutnum = bmp.skip / bmp.palette_size;
					bmp.skip = bmp.skip % bmp.palette_size;
				}
				if(clutnum == 0) {
					fin.seek(utils::file_io::SEEK::SET, pos);
					return false;
				}
			} else {
				clutnum = 0;
			}

			if(clutnum > 0) {
				if(fin.read(rgbq_, bmp.palette_size, clutnum) != clutnum) {
					fin.seek(utils::file_io::SEEK::SET, pos);
					return false;
				}
			}

			int i = 0;
			while(i < bmp.skip) {
				char c;
				if(!fin.get_char(c)) {
					fin.seek(utils::file_io::SEEK::SET, pos);
					return false;
				}
				i++;
			}

			bool f = false;
			switch(bmp.compression) {
			case BI_RGB:		// 1, 4, 8, 24, 32 bits
				if(bmp.depth == 24 || bmp.depth == 32) {
					f = read_rgb_(fin, bmp);
				} else if(bmp.depth == 1 || bmp.depth == 4 || bmp.depth == 8) {
					f = read_idx_(fin, bmp);
				}
				break;
			case BI_BITFIELDS:	// 16, 32
				f = read_bitfield_(fin, bmp);
				break;
			case BI_RLE8:
			case BI_RLE4:
				f = decompress_rle_(fin, bmp);
				break;
			default:
				break;
			}
			if(!f) {
				fin.seek(utils::file_io::SEEK::SET, pos);
			}

			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	BMP ファイルをロードする
			@param[in]	fin	ファイル I/O クラス
			@param[in]	opt	フォーマット固有の設定文字列
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool load(const char* fname, const char* opt = nullptr) noexcept
		{
			if(fname == nullptr) return false;

			utils::file_io fin;
			if(!fin.open(fname, "rb")) {
				return false;
			}
			auto ret = load(fin, opt);
			fin.close();
			return ret;
		}
	};
}
