#ifndef MEDIAINFO_PIXFMT_HPP
#define MEDIAINFO_PIXFMT_HPP

#include "libavutil/pixfmt.h"
#include <QMap>

namespace MediaInfoPixfmt
{
	const static QMap<AVPixelFormat, QString> g_pixelFormatMap =
	{
		{ AV_PIX_FMT_NONE , "NONE" },
		{ AV_PIX_FMT_YUV420P, "YUV420P" },  ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
		{ AV_PIX_FMT_YUYV422, "YUYV422" },   ///< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
		{ AV_PIX_FMT_RGB24, "RGB24" },    ///< packed RGB 8:8:8, 24bpp, RGBRGB...
		{ AV_PIX_FMT_BGR24, "BGR24" },    ///< packed RGB 8:8:8, 24bpp, BGRBGR...
		{ AV_PIX_FMT_YUV422P, "YUV422P" },   ///< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
		{ AV_PIX_FMT_YUV444P, "YUV444P" },   ///< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples)
		{ AV_PIX_FMT_YUV410P, "YUV410P" },   ///< planar YUV 4:1:0,  9bpp, (1 Cr & Cb sample per 4x4 Y samples)
		{ AV_PIX_FMT_YUV411P, "YUV411P" },   ///< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples)
		{ AV_PIX_FMT_GRAY8, "GRAY8" },     ///<        Y        ,  8bpp
		{ AV_PIX_FMT_MONOWHITE, "MONOWHITE" }, ///<        Y        ,  1bpp, 0 is white, 1 is black, in each byte pixels are ordered from the msb to the lsb
		{ AV_PIX_FMT_MONOBLACK, "MONOBLACK" }, ///<        Y        ,  1bpp, 0 is black, 1 is white, in each byte pixels are ordered from the msb to the lsb
		{ AV_PIX_FMT_PAL8, "PAL8" },      ///< 8 bits with AV_PIX_FMT_RGB32 palette
		{ AV_PIX_FMT_YUVJ420P, "YUVJ420P" },  ///< planar YUV 4:2:0, 12bpp, full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV420P and setting color_range
		{ AV_PIX_FMT_YUVJ422P, "YUVJ422P" },  ///< planar YUV 4:2:2, 16bpp, full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV422P and setting color_range
		{ AV_PIX_FMT_YUVJ444P, "YUVJ444P" },  ///< planar YUV 4:4:4, 24bpp, full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV444P and setting color_range
		{ AV_PIX_FMT_UYVY422, "UYVY422" },   ///< packed YUV 4:2:2, 16bpp, Cb Y0 Cr Y1
		{ AV_PIX_FMT_UYYVYY411, "UYYVYY411" }, ///< packed YUV 4:1:1, 12bpp, Cb Y0 Y1 Cr Y2 Y3
		{ AV_PIX_FMT_BGR8, "BGR8" },      ///< packed RGB 3:3:2,  8bpp, (msb)2B 3G 3R(lsb)
		{ AV_PIX_FMT_BGR4, "BGR4" },      ///< packed RGB 1:2:1 bitstream,  4bpp, (msb)1B 2G 1R(lsb), a byte contains two pixels, the first pixel in the byte is the one composed by the 4 msb bits
		{ AV_PIX_FMT_BGR4_BYTE, "BGR4_BYTE" }, ///< packed RGB 1:2:1,  8bpp, (msb)1B 2G 1R(lsb)
		{ AV_PIX_FMT_RGB8, "RGB8" },      ///< packed RGB 3:3:2,  8bpp, (msb)2R 3G 3B(lsb)
		{ AV_PIX_FMT_RGB4, "RGB4" },      ///< packed RGB 1:2:1 bitstream,  4bpp, (msb)1R 2G 1B(lsb), a byte contains two pixels, the first pixel in the byte is the one composed by the 4 msb bits
		{ AV_PIX_FMT_RGB4_BYTE, "RGB4_BYTE" }, ///< packed RGB 1:2:1,  8bpp, (msb)1R 2G 1B(lsb)
		{ AV_PIX_FMT_NV12, "NV12" },      ///< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V)
		{ AV_PIX_FMT_NV21, "NV21" },      ///< as above, but U and V bytes are swapped

		{ AV_PIX_FMT_ARGB, "ARGB" },     ///< packed ARGB 8:8:8:8, 32bpp, ARGBARGB...
		{ AV_PIX_FMT_RGBA, "RGBA" },      ///< packed RGBA 8:8:8:8, 32bpp, RGBARGBA...
		{ AV_PIX_FMT_ABGR, "ABGR" },      ///< packed ABGR 8:8:8:8, 32bpp, ABGRABGR...
		{ AV_PIX_FMT_BGRA, "BGRA" },      ///< packed BGRA 8:8:8:8, 32bpp, BGRABGRA...

		{ AV_PIX_FMT_GRAY16BE, "GRAY16BE" },  ///<        Y        , 16bpp, big-endian
		{ AV_PIX_FMT_GRAY16LE, "GRAY16LE" },  ///<        Y        , 16bpp, little-endian
		{ AV_PIX_FMT_YUV440P, "YUV440P" },   ///< planar YUV 4:4:0 (1 Cr & Cb sample per 1x2 Y samples)
		{ AV_PIX_FMT_YUVJ440P, "YUVJ440P" },  ///< planar YUV 4:4:0 full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV440P and setting color_range
		{ AV_PIX_FMT_YUVA420P, "YUVA420P" },  ///< planar YUV 4:2:0, 20bpp, (1 Cr & Cb sample per 2x2 Y & A samples)
		{ AV_PIX_FMT_RGB48BE, "RGB48BE" },   ///< packed RGB 16:16:16, 48bpp, 16R, 16G, 16B, the 2-byte value for each R/G/B component is stored as big-endian
		{ AV_PIX_FMT_RGB48LE, "RGB48LE" },   ///< packed RGB 16:16:16, 48bpp, 16R, 16G, 16B, the 2-byte value for each R/G/B component is stored as little-endian

		{ AV_PIX_FMT_RGB565BE, "RGB565BE" },  ///< packed RGB 5:6:5, 16bpp, (msb)   5R 6G 5B(lsb), big-endian
		{ AV_PIX_FMT_RGB565LE, "RGB565LE" },  ///< packed RGB 5:6:5, 16bpp, (msb)   5R 6G 5B(lsb), little-endian
		{ AV_PIX_FMT_RGB555BE, "RGB555BE" }, ///< packed RGB 5:5:5, 16bpp, (msb)1X 5R 5G 5B(lsb), big-endian   , X=unused/undefined
		{ AV_PIX_FMT_RGB555LE, "RGB555LE" },  ///< packed RGB 5:5:5, 16bpp, (msb)1X 5R 5G 5B(lsb), little-endian, X=unused/undefined

		{ AV_PIX_FMT_BGR565BE, "BGR565BE" },  ///< packed BGR 5:6:5, 16bpp, (msb)   5B 6G 5R(lsb), big-endian
		{ AV_PIX_FMT_BGR565LE, "BGR565LE" },  ///< packed BGR 5:6:5, 16bpp, (msb)   5B 6G 5R(lsb), little-endian
		{ AV_PIX_FMT_BGR555BE, "BGR555BE" },  ///< packed BGR 5:5:5, 16bpp, (msb)1X 5B 5G 5R(lsb), big-endian   , X=unused/undefined
		{ AV_PIX_FMT_BGR555LE, "BGR555LE" },  ///< packed BGR 5:5:5, 16bpp, (msb)1X 5B 5G 5R(lsb), little-endian, X=unused/undefined

#if FF_API_VAAPI
		/** @name Deprecated pixel formats */
		/**@{*/
		{ AV_PIX_FMT_VAAPI_MOCO, "MOCO" }, ///< HW acceleration through VA API at motion compensation entry-point, Picture.data[3] contains a vaapi_render_state struct which contains macroblocks as well as various fields extracted from headers
		{ AV_PIX_FMT_VAAPI_IDCT, "IDCT" }, ///< HW acceleration through VA API at IDCT entry-point, Picture.data[3] contains a vaapi_render_state struct which contains fields extracted from headers
		{ AV_PIX_FMT_VAAPI_VLD, "VLD" },  ///< HW decoding through VA API, Picture.data[3] contains a VASurfaceID
		/**@}*/
		{ AV_PIX_FMT_VAAPI, "VAAPI" },
#else
											  /**
											  *  Hardware acceleration through VA-API, data[3] contains a
											  *  VASurfaceID.
											  */
		{ AV_PIX_FMT_VAAPI, "VAAPI" },
#endif

		{ AV_PIX_FMT_YUV420P16LE, "YUV420P16LE" },  ///< planar YUV 4:2:0, 24bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
		{ AV_PIX_FMT_YUV420P16BE, "YUV420P16BE" },  ///< planar YUV 4:2:0, 24bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
		{ AV_PIX_FMT_YUV422P16LE, "YUV422P16LE" },  ///< planar YUV 4:2:2, 32bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
		{ AV_PIX_FMT_YUV422P16BE, "YUV422P16BE" }, ///< planar YUV 4:2:2, 32bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV444P16LE, "YUV444P16LE" }, ///< planar YUV 4:4:4, 48bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
		{ AV_PIX_FMT_YUV444P16BE, "YUV444P16BE" }, ///< planar YUV 4:4:4, 48bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
		{ AV_PIX_FMT_DXVA2_VLD, "DXVA2_VLD" },   ///< HW decoding through DXVA2, Picture.data[3] contains a LPDIRECT3DSURFACE9 pointer

		{ AV_PIX_FMT_RGB444LE, "RGB444LE" }, ///< packed RGB 4:4:4, 16bpp, (msb)4X 4R 4G 4B(lsb), little-endian, X=unused/undefined
		{ AV_PIX_FMT_RGB444BE, "RGB444BE" }, ///< packed RGB 4:4:4, 16bpp, (msb)4X 4R 4G 4B(lsb), big-endian,    X=unused/undefined
		{ AV_PIX_FMT_BGR444LE, "BGR444LE" }, ///< packed BGR 4:4:4, 16bpp, (msb)4X 4B 4G 4R(lsb), little-endian, X=unused/undefined
		{ AV_PIX_FMT_BGR444BE, "BGR444BE" }, ///< packed BGR 4:4:4, 16bpp, (msb)4X 4B 4G 4R(lsb), big-endian,    X=unused/undefined
		{ AV_PIX_FMT_YA8, "YA8" },      ///< 8 bits gray, 8 bits alpha

		{ AV_PIX_FMT_Y400A, "Y400A" }, ///< alias for AV_PIX_FMT_YA8
		{ AV_PIX_FMT_GRAY8A, "GRAY8A" }, ///< alias for AV_PIX_FMT_YA8

		{ AV_PIX_FMT_BGR48BE, "BGR48BE" },  ///< packed RGB 16:16:16, 48bpp, 16B, 16G, 16R, the 2-byte value for each R/G/B component is stored as big-endian
		{ AV_PIX_FMT_BGR48LE, "BGR48LE" },  ///< packed RGB 16:16:16, 48bpp, 16B, 16G, 16R, the 2-byte value for each R/G/B component is stored as little-endian

		/**
		* The following 12 formats have the disadvantage of needing 1 format for each bit depth.
		* Notice that each 9/10 bits sample is stored in 16 bits with extra padding.
		* If you want to support multiple bit depths, then using AV_PIX_FMT_YUV420P16* with the bpp stored separately is better.
		*/
		{ AV_PIX_FMT_YUV420P9BE, "YUV420P9BE" }, ///< planar YUV 4:2:0, 13.5bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
		{ AV_PIX_FMT_YUV420P9LE, "YUV420P9LE" },///< planar YUV 4:2:0, 13.5bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
		{ AV_PIX_FMT_YUV420P10BE, "YUV420P10BE" },///< planar YUV 4:2:0, 15bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
		{ AV_PIX_FMT_YUV420P10LE, "YUV420P10LE" },///< planar YUV 4:2:0, 15bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
		{ AV_PIX_FMT_YUV422P10BE, "YUV422P10BE" },///< planar YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV422P10LE, "YUV422P10LE" },///< planar YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
		{ AV_PIX_FMT_YUV444P9BE, "YUV444P9BE" },///< planar YUV 4:4:4, 27bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV444P9LE, "YUV444P9LE" },///< planar YUV 4:4:4, 27bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
		{ AV_PIX_FMT_YUV444P10BE, "YUV444P10BE" },///< planar YUV 4:4:4, 30bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV444P10LE, "YUV444P10LE" },///< planar YUV 4:4:4, 30bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
		{ AV_PIX_FMT_YUV422P9BE, "YUV422P9BE" },///< planar YUV 4:2:2, 18bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV422P9LE, "YUV422P9LE" },///< planar YUV 4:2:2, 18bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
		{ AV_PIX_FMT_GBRP, "GBRP" },     ///< planar GBR 4:4:4 24bpp
		{ AV_PIX_FMT_GBR24P, "GBR24P" },// alias for #AV_PIX_FMT_GBRP
		{ AV_PIX_FMT_GBRP9BE, "GBRP9BE" },  ///< planar GBR 4:4:4 27bpp, big-endian
		{ AV_PIX_FMT_GBRP9LE, "GBRP9LE" },  ///< planar GBR 4:4:4 27bpp, little-endian
		{ AV_PIX_FMT_GBRP10BE, "GBRP10BE" }, ///< planar GBR 4:4:4 30bpp, big-endian
		{ AV_PIX_FMT_GBRP10LE, "GBRP10LE" }, ///< planar GBR 4:4:4 30bpp, little-endian
		{ AV_PIX_FMT_GBRP16BE, "GBRP16BE" }, ///< planar GBR 4:4:4 48bpp, big-endian
		{ AV_PIX_FMT_GBRP16LE, "GBRP16LE" }, ///< planar GBR 4:4:4 48bpp, little-endian
		{ AV_PIX_FMT_YUVA422P, "YUVA422P" }, ///< planar YUV 4:2:2 24bpp, (1 Cr & Cb sample per 2x1 Y & A samples)
		{ AV_PIX_FMT_YUVA444P, "YUVA444P" }, ///< planar YUV 4:4:4 32bpp, (1 Cr & Cb sample per 1x1 Y & A samples)
		{ AV_PIX_FMT_YUVA420P9BE, "YUVA420P9BE" }, ///< planar YUV 4:2:0 22.5bpp, (1 Cr & Cb sample per 2x2 Y & A samples), big-endian
		{ AV_PIX_FMT_YUVA420P9LE, "YUVA420P9LE" }, ///< planar YUV 4:2:0 22.5bpp, (1 Cr & Cb sample per 2x2 Y & A samples), little-endian
		{ AV_PIX_FMT_YUVA422P9BE, "YUVA422P9BE" }, ///< planar YUV 4:2:2 27bpp, (1 Cr & Cb sample per 2x1 Y & A samples), big-endian
		{ AV_PIX_FMT_YUVA422P9LE, "YUVA422P9LE" }, ///< planar YUV 4:2:2 27bpp, (1 Cr & Cb sample per 2x1 Y & A samples), little-endian
		{ AV_PIX_FMT_YUVA444P9BE, "YUVA444P9BE" }, ///< planar YUV 4:4:4 36bpp, (1 Cr & Cb sample per 1x1 Y & A samples), big-endian
		{ AV_PIX_FMT_YUVA444P9LE, "YUVA444P9LE" }, ///< planar YUV 4:4:4 36bpp, (1 Cr & Cb sample per 1x1 Y & A samples), little-endian
		{ AV_PIX_FMT_YUVA420P10BE, "YUVA420P10BE" },///< planar YUV 4:2:0 25bpp, (1 Cr & Cb sample per 2x2 Y & A samples, big-endian)
		{ AV_PIX_FMT_YUVA420P10LE, "YUVA420P10LE" },///< planar YUV 4:2:0 25bpp, (1 Cr & Cb sample per 2x2 Y & A samples, little-endian)
		{ AV_PIX_FMT_YUVA422P10BE, "YUVA422P10BE" },///< planar YUV 4:2:2 30bpp, (1 Cr & Cb sample per 2x1 Y & A samples, big-endian)
		{ AV_PIX_FMT_YUVA422P10LE, "YUVA422P10LE" },///< planar YUV 4:2:2 30bpp, (1 Cr & Cb sample per 2x1 Y & A samples, little-endian)
		{ AV_PIX_FMT_YUVA444P10BE, "YUVA444P10BE" },///< planar YUV 4:4:4 40bpp, (1 Cr & Cb sample per 1x1 Y & A samples, big-endian)
		{ AV_PIX_FMT_YUVA444P10LE, "YUVA444P10LE" },///< planar YUV 4:4:4 40bpp, (1 Cr & Cb sample per 1x1 Y & A samples, little-endian)
		{ AV_PIX_FMT_YUVA420P16BE, "YUVA420P16BE" },///< planar YUV 4:2:0 40bpp, (1 Cr & Cb sample per 2x2 Y & A samples, big-endian)
		{ AV_PIX_FMT_YUVA420P16LE, "YUVA420P16LE" },///< planar YUV 4:2:0 40bpp, (1 Cr & Cb sample per 2x2 Y & A samples, little-endian)
		{ AV_PIX_FMT_YUVA422P16BE, "YUVA422P16BE" },///< planar YUV 4:2:2 48bpp, (1 Cr & Cb sample per 2x1 Y & A samples, big-endian)
		{ AV_PIX_FMT_YUVA422P16LE, "YUVA422P16LE" },///< planar YUV 4:2:2 48bpp, (1 Cr & Cb sample per 2x1 Y & A samples, little-endian)
		{ AV_PIX_FMT_YUVA444P16BE, "YUVA444P16BE" },///< planar YUV 4:4:4 64bpp, (1 Cr & Cb sample per 1x1 Y & A samples, big-endian)
		{ AV_PIX_FMT_YUVA444P16LE, "YUVA444P16LE" },///< planar YUV 4:4:4 64bpp, (1 Cr & Cb sample per 1x1 Y & A samples, little-endian)

		{ AV_PIX_FMT_VDPAU, "VDPAU" },    ///< HW acceleration through VDPAU, Picture.data[3] contains a VdpVideoSurface

		{ AV_PIX_FMT_XYZ12LE, "XYZ12LE" },     ///< packed XYZ 4:4:4, 36 bpp, (msb) 12X, 12Y, 12Z (lsb), the 2-byte value for each X/Y/Z is stored as little-endian, the 4 lower bits are set to 0
		{ AV_PIX_FMT_XYZ12BE, "XYZ12BE" },     ///< packed XYZ 4:4:4, 36 bpp, (msb) 12X, 12Y, 12Z (lsb), the 2-byte value for each X/Y/Z is stored as big-endian, the 4 lower bits are set to 0
		{ AV_PIX_FMT_NV16, "NV16" },        ///< interleaved chroma YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
		{ AV_PIX_FMT_NV20LE, "NV20LE" },      ///< interleaved chroma YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
		{ AV_PIX_FMT_NV20BE, "NV20BE" },      ///< interleaved chroma YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian

		{ AV_PIX_FMT_RGBA64BE, "RGBA64BE" },    ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
		{ AV_PIX_FMT_RGBA64LE, "RGBA64LE" },    ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian
		{ AV_PIX_FMT_BGRA64BE, "BGRA64BE" },    ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
		{ AV_PIX_FMT_BGRA64LE, "BGRA64LE" },    ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian

		{ AV_PIX_FMT_YVYU422, "YVYU422" },  ///< packed YUV 4:2:2, 16bpp, Y0 Cr Y1 Cb

		{ AV_PIX_FMT_YA16BE, "YA16BE" },      ///< 16 bits gray, 16 bits alpha (big-endian)
		{ AV_PIX_FMT_YA16LE, "YA16LE" },      ///< 16 bits gray, 16 bits alpha (little-endian)

		{ AV_PIX_FMT_GBRAP, "GBRAP" },       ///< planar GBRA 4:4:4:4 32bpp
		{ AV_PIX_FMT_GBRAP16BE, "GBRAP16BE" },   ///< planar GBRA 4:4:4:4 64bpp, big-endian
		{ AV_PIX_FMT_GBRAP16LE, "GBRAP16LE" },   ///< planar GBRA 4:4:4:4 64bpp, little-endian
												 /**
												 *  HW acceleration through QSV, data[3] contains a pointer to the
												 *  mfxFrameSurface1 structure.
												 */
		{ AV_PIX_FMT_QSV, "QSV" },
		/**
		* HW acceleration though MMAL, data[3] contains a pointer to the
		* MMAL_BUFFER_HEADER_T structure.
		*/
		{ AV_PIX_FMT_MMAL, "MMAL" },

		{ AV_PIX_FMT_D3D11VA_VLD, "D3D11VA_VLD" }, ///< HW decoding through Direct3D11 via old API, Picture.data[3] contains a ID3D11VideoDecoderOutputView pointer

												   /**
												   * HW acceleration through CUDA. data[i] contain CUdeviceptr pointers
												   * exactly as for system memory frames.
												   */
		{ AV_PIX_FMT_CUDA, "CUDA" },

		{ AV_PIX_FMT_0RGB, "0RGB" },       ///< packed RGB 8:8:8, 32bpp, XRGBXRGB...   X=unused/undefined
		{ AV_PIX_FMT_RGB0, "RGB0" },       ///< packed RGB 8:8:8, 32bpp, RGBXRGBX...   X=unused/undefined
		{ AV_PIX_FMT_0BGR, "0BGR" },       ///< packed BGR 8:8:8, 32bpp, XBGRXBGR...   X=unused/undefined
		{ AV_PIX_FMT_BGR0, "BGR0" },       ///< packed BGR 8:8:8, 32bpp, BGRXBGRX...   X=unused/undefined

		{ AV_PIX_FMT_YUV420P12BE, "YUV420P12BE" },///< planar YUV 4:2:0,18bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
		{ AV_PIX_FMT_YUV420P12LE, "YUV420P12LE" },///< planar YUV 4:2:0,18bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
		{ AV_PIX_FMT_YUV420P14BE, "YUV420P14BE" },///< planar YUV 4:2:0,21bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
		{ AV_PIX_FMT_YUV420P14LE, "YUV420P14LE" },///< planar YUV 4:2:0,21bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
		{ AV_PIX_FMT_YUV422P12BE, "YUV422P12BE" },///< planar YUV 4:2:2,24bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV422P12LE, "YUV422P12LE" },///< planar YUV 4:2:2,24bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
		{ AV_PIX_FMT_YUV422P14BE, "YUV422P14BE" },///< planar YUV 4:2:2,28bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV422P14LE, "YUV422P14LE" }, ///< planar YUV 4:2:2,28bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
		{ AV_PIX_FMT_YUV444P12BE, "YUV444P12BE" },///< planar YUV 4:4:4,36bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV444P12LE, "YUV444P12LE" },///< planar YUV 4:4:4,36bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
		{ AV_PIX_FMT_YUV444P14BE, "YUV444P14BE" },///< planar YUV 4:4:4,42bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
		{ AV_PIX_FMT_YUV444P14LE, "YUV444P14LE" },///< planar YUV 4:4:4,42bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
		{ AV_PIX_FMT_GBRP12BE, "GBRP12BE" },   ///< planar GBR 4:4:4 36bpp, big-endian
		{ AV_PIX_FMT_GBRP12LE, "GBRP12LE" },   ///< planar GBR 4:4:4 36bpp, little-endian
		{ AV_PIX_FMT_GBRP14BE, "GBRP14BE" },   ///< planar GBR 4:4:4 42bpp, big-endian
		{ AV_PIX_FMT_GBRP14LE, "GBRP14LE" },  ///< planar GBR 4:4:4 42bpp, little-endian
		{ AV_PIX_FMT_YUVJ411P, "YUVJ411P" },  ///< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples) full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV411P and setting color_range

		{ AV_PIX_FMT_BAYER_BGGR8, "BAYER_BGGR8" },   ///< bayer, BGBG..(odd line), GRGR..(even line), 8-bit samples */
		{ AV_PIX_FMT_BAYER_RGGB8, "BAYER_RGGB8" },   ///< bayer, RGRG..(odd line), GBGB..(even line), 8-bit samples */
		{ AV_PIX_FMT_BAYER_GBRG8, "BAYER_GBRG8" },   ///< bayer, GBGB..(odd line), RGRG..(even line), 8-bit samples */
		{ AV_PIX_FMT_BAYER_GRBG8, "BAYER_GRBG8" },   ///< bayer, GRGR..(odd line), BGBG..(even line), 8-bit samples */
		{ AV_PIX_FMT_BAYER_BGGR16LE, "BAYER_BGGR16LE" },///< bayer, BGBG..(odd line), GRGR..(even line), 16-bit samples, little-endian */
		{ AV_PIX_FMT_BAYER_BGGR16BE, "BAYER_BGGR16BE" },///< bayer, BGBG..(odd line), GRGR..(even line), 16-bit samples, big-endian */
		{ AV_PIX_FMT_BAYER_RGGB16LE, "BAYER_RGGB16LE" },///< bayer, RGRG..(odd line), GBGB..(even line), 16-bit samples, little-endian */
		{ AV_PIX_FMT_BAYER_RGGB16BE, "BAYER_RGGB16BE" },///< bayer, RGRG..(odd line), GBGB..(even line), 16-bit samples, big-endian */
		{ AV_PIX_FMT_BAYER_GBRG16LE, "BAYER_GBRG16LE" },///< bayer, GBGB..(odd line), RGRG..(even line), 16-bit samples, little-endian */
		{ AV_PIX_FMT_BAYER_GBRG16BE, "BAYER_GBRG16BE" },///< bayer, GBGB..(odd line), RGRG..(even line), 16-bit samples, big-endian */
		{ AV_PIX_FMT_BAYER_GRBG16LE, "BAYER_GRBG16LE" },///< bayer, GRGR..(odd line), BGBG..(even line), 16-bit samples, little-endian */
		{ AV_PIX_FMT_BAYER_GRBG16BE, "BAYER_GRBG16BE" },///< bayer, GRGR..(odd line), BGBG..(even line), 16-bit samples, big-endian */

		{ AV_PIX_FMT_XVMC, "XVMC" },///< XVideo Motion Acceleration via common packet passing

		{ AV_PIX_FMT_YUV440P10LE, "YUV440P10LE" },///< planar YUV 4:4:0,20bpp, (1 Cr & Cb sample per 1x2 Y samples), little-endian
		{ AV_PIX_FMT_YUV440P10BE, "YUV440P10BE" },///< planar YUV 4:4:0,20bpp, (1 Cr & Cb sample per 1x2 Y samples), big-endian
		{ AV_PIX_FMT_YUV440P12LE, "YUV440P12LE" },///< planar YUV 4:4:0,24bpp, (1 Cr & Cb sample per 1x2 Y samples), little-endian
		{ AV_PIX_FMT_YUV440P12BE, "YUV440P12BE" },///< planar YUV 4:4:0,24bpp, (1 Cr & Cb sample per 1x2 Y samples), big-endian
		{ AV_PIX_FMT_AYUV64LE, "AYUV64LE" },   ///< packed AYUV 4:4:4,64bpp (1 Cr & Cb sample per 1x1 Y & A samples), little-endian
		{ AV_PIX_FMT_AYUV64BE, "AYUV64BE" },   ///< packed AYUV 4:4:4,64bpp (1 Cr & Cb sample per 1x1 Y & A samples), big-endian

		{ AV_PIX_FMT_VIDEOTOOLBOX, "" },///< hardware decoding through Videotoolbox

		{ AV_PIX_FMT_P010LE, "P010LE" },///< like NV12, with 10bpp per component, data in the high bits, zeros in the low bits, little-endian
		{ AV_PIX_FMT_P010BE, "P010BE" },///< like NV12, with 10bpp per component, data in the high bits, zeros in the low bits, big-endian

		{ AV_PIX_FMT_GBRAP12BE, "GBRAP12BE" }, ///< planar GBR 4:4:4:4 48bpp, big-endian
		{ AV_PIX_FMT_GBRAP12LE, "GBRAP12LE" }, ///< planar GBR 4:4:4:4 48bpp, little-endian

		{ AV_PIX_FMT_GBRAP10BE, "GBRAP10BE" }, ///< planar GBR 4:4:4:4 40bpp, big-endian
		{ AV_PIX_FMT_GBRAP10LE, "GBRAP10LE" }, ///< planar GBR 4:4:4:4 40bpp, little-endian

		{ AV_PIX_FMT_MEDIACODEC, "MEDIACODEC" },///< hardware decoding through MediaCodec

		{ AV_PIX_FMT_GRAY12BE, "GRAY12BE" },  ///<        Y        , 12bpp, big-endian
		{ AV_PIX_FMT_GRAY12LE, "GRAY12LE" },  ///<        Y        , 12bpp, little-endian
		{ AV_PIX_FMT_GRAY10BE, "GRAY10BE" },  ///<        Y        , 10bpp, big-endian
		{ AV_PIX_FMT_GRAY10LE, "GRAY10LE" },  ///<        Y        , 10bpp, little-endian

		{ AV_PIX_FMT_P016LE, "P016LE" },///< like NV12, with 16bpp per component, little-endian
		{ AV_PIX_FMT_P016BE, "P016BE" },///< like NV12, with 16bpp per component, big-endian

		/**
		* Hardware surfaces for Direct3D11.
		*
		* This is preferred over the legacy AV_PIX_FMT_D3D11VA_VLD. The new D3D11
		* hwaccel API and filtering support AV_PIX_FMT_D3D11 only.
		*
		* data[0] contains a ID3D11Texture2D pointer, and data[1] contains the
		* texture array index of the frame as intptr_t if the ID3D11Texture2D is
		* an array texture (or always 0 if it's a normal texture).
		*/
		{ AV_PIX_FMT_D3D11, "D3D11" },

		{ AV_PIX_FMT_GRAY9BE, "GRAY9BE" },  ///<        Y        , 9bpp, big-endian
		{ AV_PIX_FMT_GRAY9LE, "GRAY9LE" },  ///<        Y        , 9bpp, little-endian

		{ AV_PIX_FMT_GBRPF32BE, "GBRPF32BE" }, ///< IEEE-754 single precision planar GBR 4:4:4,     96bpp, big-endian
		{ AV_PIX_FMT_GBRPF32LE, "GBRPF32LE" }, ///< IEEE-754 single precision planar GBR 4:4:4,     96bpp, little-endian
		{ AV_PIX_FMT_GBRAPF32BE, "GBRAPF32BE" },///< IEEE-754 single precision planar GBRA 4:4:4:4, 128bpp, big-endian
		{ AV_PIX_FMT_GBRAPF32LE, "GBRAPF32LE" },///< IEEE-754 single precision planar GBRA 4:4:4:4, 128bpp, little-endian

		/**
		* DRM-managed buffers exposed through PRIME buffer sharing.
		*
		* data[0] points to an AVDRMFrameDescriptor.
		*/
		{ AV_PIX_FMT_DRM_PRIME, "DRM_PRIME" },
		/**
		* Hardware surfaces for OpenCL.
		*
		* data[i] contain 2D image objects (typed in C as cl_mem, used
		* in OpenCL as image2d_t) for each plane of the surface.
		*/
		{ AV_PIX_FMT_OPENCL, "OPENCL" },

		{ AV_PIX_FMT_GRAY14BE, "GRAY14BE" },  ///<        Y        , 14bpp, big-endian
		{ AV_PIX_FMT_GRAY14LE, "GRAY14LE" },  ///<        Y        , 14bpp, little-endian

		{ AV_PIX_FMT_GRAYF32BE, "GRAYF32BE" }, ///< IEEE-754 single precision Y, 32bpp, big-endian
		{ AV_PIX_FMT_GRAYF32LE, "GRAYF32LE" }, ///< IEEE-754 single precision Y, 32bpp, little-endian

		{ AV_PIX_FMT_NB, QString() },        ///< number of pixel formats, DO NOT USE THIS if you want to link with shared libav* because the number of formats might differ between versions
	};

	QString getPixelFormat(const AVPixelFormat &a_pixfmt)
	{
        return g_pixelFormatMap.contains(a_pixfmt) ? g_pixelFormatMap[a_pixfmt] : QString();
	}
};

#endif // MEDIAINFO_PIXFMT_HPP
