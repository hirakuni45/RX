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

namespace image {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	BMP 形式ファイルクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class bmp_in {

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

#if 0
		/* Constants for the biCompression field */
	#ifndef BI_RGB
		static const uint16_t BI_RGB				0L		/* Uncompressed        */
		static const uint16_t BI_RLE8				1L		/* RLE (8 bits/pixel)  */
		static const uint16_t BI_RLE4				2L		/* RLE (4 bits/pixel)  */
		static const uint16_t BI_BITFIELDS		3L		/* Bitfield            */
		static const uint16_t BI_JPEG				4L		/* JPEG Extension      */
		static const uint16_t BI_PNG				5L		/* PNG Extension       */
	#endif

		static const uint16_t BMP_MAX_WIDTH	16384		/* 許容される最大サイズ */
		static const uint16_t BMP_MAX_HEIGHT	16384		/* 許容される最大サイズ */
#endif

		struct BGRA_PAD {
			unsigned int	b;
			unsigned int	g;
			unsigned int	r;
			unsigned int	a;
		};

		struct bmp_info {
			int		offbits;
			int		bihsize;
			int		skip;
			unsigned int	width;
			unsigned int	height;
			int		depth;
			int		compression;
			int		palette_size;

			BGRA_PAD	color_mask;
			bool	topdown;
			bool	alpha_chanel;
		};

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
			unsigned char bfh[FILEHED_SIZE + BMPV5HED_SIZE];
			unsigned char *const bih = bfh + FILEHED_SIZE;

			// skip MAC-Binary header がある場合を考えてヘッダーを特定
			for(int i = 0; i < 512; i++) {
				if(fin.read(bfh, (FILEHED_SIZE + BIHSIZE_SIZE), 1) != 1) {
					return false;
				}
				if(mgetwl(bfh + BFH_WTYPE) == BMP_SIGNATURE) break;
				if(i != 0) {
					return false;
				}
				if(fin.read(bfh, (128 - FILEHED_SIZE - BIHSIZE_SIZE), 1) != 1) {
					return false;
				}
			}

			bmp.offbits = mgetdwl(bfh + BFH_DOFFBITS);
			bmp.bihsize = mgetdwl(bfh + BFH_DBIHSIZE);
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
				bmp.width  = mgetdwl(bih + BIH_LWIDTH);
				bmp.height = mgetdwl(bih + BIH_LHEIGHT);
				bmp.depth  = mgetwl(bih + BIH_WBITCOUNT);
				bmp.compression   = mgetdwl(bih + BIH_DCOMPRESSION);
				bmp.palette_size  = RGBQUAD_SIZE;
				if(static_cast<int>(bmp.height) < 0) {
					bmp.height  = -static_cast<int>(bmp.height);
					bmp.topdown = true;
				}
			} else {
			// [OS/2] style BMP
				bmp.width  = mgetwl(bih + BCH_WWIDTH);
				bmp.height = mgetwl(bih + BCH_WHEIGHT);
				bmp.depth  = mgetwl(bih + BCH_WBITCOUNT);
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
				bmp.color_mask.r = mgetdwl(bih + B4H_DREDMASK);
				bmp.color_mask.g = mgetdwl(bih + B4H_DGREENMASK);
				bmp.color_mask.b = mgetdwl(bih + B4H_DBLUEMASK);

				if(bmp.depth == 32 && bmp.bihsize >= (INFOHED_SIZE + 16)) {
					bmp.color_mask.a = mgetdwl(bih + B4H_DALPHAMASK);
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
		bool read_idx_(utils::file_io& fin, shared_img img, const bmp_info& bmp)
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
			for(unsigned int h = 0; h < bmp.height; ++h) {
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
///					img::idx8 c;
///					c.i = idx;
///					img->put_pixel(pos, c);
				}
				pos.y += d;
				++prgl_pos_;
			}
			return true;
		}


		/*------------------------------------------------------/
		/	BGR (無圧縮 24/32 ビット) 形式の画像データを展開	/
		/------------------------------------------------------*/
		bool read_rgb_(utils::file_io& fin, shared_img img, const bmp_info& bmp)
		{
			int pads = bmp.depth / 8;
			size_t stride = bmp.width * pads;
			if(stride & 3) stride += 4 - (stride & 3);

			char[stride] tmp;;
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
			for(unsigned int h = 0; h < bmp.height; ++h) {
				if(fin.read(buf, 1, stride) != stride) {
					return false;
				}
				char* src = buf;
				for(pos.x = 0; pos.x < bmp.width; ++pos.x) {
					img::rgba8 c;
					c.r = src[2];
					c.g = src[1];
					c.b = src[0];
					c.a = 255;
					img->put_pixel(pos, c);
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
		bool read_bitfield_(utils::file_io& fin, shared_img img, const bmp_info& bmp)
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
			for(uint32_t h = 0; h < bmp.height; ++h) {
				if(fin.read(rowb, 1, stride) != stride) {
					return false;
				}

			char* src = rowb;
			switch(bmp.depth) {
			case 16:
				{
					for(pos.x = 0; pos.x < bmp.width; ++pos.x) {
						unsigned int v = *(unsigned char *)src++;
						v |= ( *(unsigned char *)src++ ) << 8;
						rgba8 c;
						c.r = (v & bmp.color_mask.r) >> (shift_cnt.r - bits_cnt.r);
						c.g = (v & bmp.color_mask.g) >> (shift_cnt.g - bits_cnt.g);
						c.b = (v & bmp.color_mask.b) >> (shift_cnt.b - bits_cnt.b);
						c.r = (c.r << (8 - bits_cnt.r)) | (c.r >> (8 - bits_cnt.r));
						c.g = (c.g << (8 - bits_cnt.g)) | (c.g >> (8 - bits_cnt.g));
						c.b = (c.b << (8 - bits_cnt.b)) | (c.b >> (8 - bits_cnt.b));
						c.a = 255;
						img->put_pixel(pos, c);
					}
				}
				break;

			case 32:
				{
					for(pos.x = 0; pos.x < bmp.width; ++pos.x) {
						rgba8 c;
						c.r = src[2];
						c.g = src[1];
						c.b = src[0];
						if(img->test_alpha()) c.a = src[3];
						else c.a = 255;
						src += 4;
						img->put_pixel(pos, c);
					}
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
		bool decompress_rle_(utils::file_io& fin, shared_img img, const bmp_info& bmp)
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
					idx8 c(bfptr[1]);
					switch(bmp.depth) {
					case 8:						/* BI_RLE8 */
						while(n > 0 && pos.x < bmp.width) {
							img->put_pixel(pos, c);
							--n;
							++pos.x;
						}
						break;
					case 4:						/* BI_RLE4 */
						int o = 0;
						idx8 c0(c.i >> 4);
						idx8 c1(c.i & 0xf);
						while(n > 0 && pos.x < bmp.width) {
							if(o & 1) img->put_pixel(pos, c1);
							else img->put_pixel(pos, c0);
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
							idx8 c( *p++ );
							img->put_pixel(pos, c);
							--n;
							++pos.x;
						}
						break;
					case 4:						/* BI_RLE4 */
						int o = 0;
						while(n > 0 && pos.x < bmp.width) {
							idx8 c0(p[o >> 1] >> 4);
							idx8 c1(p[o >> 1] & 0xf);
							if(o & 1) img->put_pixel(pos, c1);
							else img->put_pixel(pos, c0);
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
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		bmp_in() { }



	};
}
