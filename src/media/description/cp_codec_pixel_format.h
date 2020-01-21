/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-07

Description:

**************************************************************************/

#ifndef _CP_CODEC_PIXEL_FORMAT_INCLUDE_H_
#define _CP_CODEC_PIXEL_FORMAT_INCLUDE_H_




//typedef	enum cp_codec_pixel_format_enum					cp_codec_pixel_format_e;



#pragma pack(1)

typedef	enum cp_codec_pixel_format_enum
{
	cp_codec_pixel_format_none = -1,
	cp_codec_pixel_format_yuv420p,   ///< planar yuv 4:2:0, 12bpp, (1 cr & cb sample per 2x2 y samples)
	cp_codec_pixel_format_yuyv422,   ///< packed yuv 4:2:2, 16bpp, y0 cb y1 cr
	cp_codec_pixel_format_rgb24,     ///< packed rgb 8:8:8, 24bpp, rgbrgb...
	cp_codec_pixel_format_bgr24,     ///< packed rgb 8:8:8, 24bpp, bgrbgr...
	cp_codec_pixel_format_yuv422p,   ///< planar yuv 4:2:2, 16bpp, (1 cr & cb sample per 2x1 y samples)
	cp_codec_pixel_format_yuv444p,   ///< planar yuv 4:4:4, 24bpp, (1 cr & cb sample per 1x1 y samples)
	cp_codec_pixel_format_yuv410p,   ///< planar yuv 4:1:0,  9bpp, (1 cr & cb sample per 4x4 y samples)
	cp_codec_pixel_format_yuv411p,   ///< planar yuv 4:1:1, 12bpp, (1 cr & cb sample per 4x1 y samples)
	cp_codec_pixel_format_gray8,     ///<        y        ,  8bpp
	cp_codec_pixel_format_monowhite, ///<        y        ,  1bpp, 0 is white, 1 is black, in each byte pixels are ordered from the msb to the lsb
	cp_codec_pixel_format_monoblack, ///<        y        ,  1bpp, 0 is black, 1 is white, in each byte pixels are ordered from the msb to the lsb
	cp_codec_pixel_format_pal8,      ///< 8 bits with cp_codec_pixel_format_rgb32 palette
	cp_codec_pixel_format_yuvj420p,  ///< planar yuv 4:2:0, 12bpp, full scale (jpeg), deprecated in favor of cp_codec_pixel_format_yuv420p and setting color_range
	cp_codec_pixel_format_yuvj422p,  ///< planar yuv 4:2:2, 16bpp, full scale (jpeg), deprecated in favor of cp_codec_pixel_format_yuv422p and setting color_range
	cp_codec_pixel_format_yuvj444p,  ///< planar yuv 4:4:4, 24bpp, full scale (jpeg), deprecated in favor of cp_codec_pixel_format_yuv444p and setting color_range
#if ff_api_xvmc
	cp_codec_pixel_format_xvmc_mpeg2_mc,///< xvideo motion acceleration via common packet passing
	cp_codec_pixel_format_xvmc_mpeg2_idct,
	cp_codec_pixel_format_xvmc = cp_codec_pixel_format_xvmc_mpeg2_idct,
#endif /* ff_api_xvmc */
	cp_codec_pixel_format_uyvy422,   ///< packed yuv 4:2:2, 16bpp, cb y0 cr y1
	cp_codec_pixel_format_uyyvyy411, ///< packed yuv 4:1:1, 12bpp, cb y0 y1 cr y2 y3
	cp_codec_pixel_format_bgr8,      ///< packed rgb 3:3:2,  8bpp, (msb)2b 3g 3r(lsb)
	cp_codec_pixel_format_bgr4,      ///< packed rgb 1:2:1 bitstream,  4bpp, (msb)1b 2g 1r(lsb), a byte contains two pixels, the first pixel in the byte is the one composed by the 4 msb bits
	cp_codec_pixel_format_bgr4_byte, ///< packed rgb 1:2:1,  8bpp, (msb)1b 2g 1r(lsb)
	cp_codec_pixel_format_rgb8,      ///< packed rgb 3:3:2,  8bpp, (msb)2r 3g 3b(lsb)
	cp_codec_pixel_format_rgb4,      ///< packed rgb 1:2:1 bitstream,  4bpp, (msb)1r 2g 1b(lsb), a byte contains two pixels, the first pixel in the byte is the one composed by the 4 msb bits
	cp_codec_pixel_format_rgb4_byte, ///< packed rgb 1:2:1,  8bpp, (msb)1r 2g 1b(lsb)
	cp_codec_pixel_format_nv12,      ///< planar yuv 4:2:0, 12bpp, 1 plane for y and 1 plane for the uv components, which are interleaved (first byte u and the following byte v)
	cp_codec_pixel_format_nv21,      ///< as above, but u and v bytes are swapped

	cp_codec_pixel_format_argb,      ///< packed argb 8:8:8:8, 32bpp, argbargb...
	cp_codec_pixel_format_rgba,      ///< packed rgba 8:8:8:8, 32bpp, rgbargba...
	cp_codec_pixel_format_abgr,      ///< packed abgr 8:8:8:8, 32bpp, abgrabgr...
	cp_codec_pixel_format_bgra,      ///< packed bgra 8:8:8:8, 32bpp, bgrabgra...

	cp_codec_pixel_format_gray16be,  ///<        y        , 16bpp, big-endian
	cp_codec_pixel_format_gray16le,  ///<        y        , 16bpp, little-endian
	cp_codec_pixel_format_yuv440p,   ///< planar yuv 4:4:0 (1 cr & cb sample per 1x2 y samples)
	cp_codec_pixel_format_yuvj440p,  ///< planar yuv 4:4:0 full scale (jpeg), deprecated in favor of cp_codec_pixel_format_yuv440p and setting color_range
	cp_codec_pixel_format_yuva420p,  ///< planar yuv 4:2:0, 20bpp, (1 cr & cb sample per 2x2 y & a samples)
#if ff_api_vdpau
	cp_codec_pixel_format_vdpau_h264,///< h.264 hw decoding with vdpau, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
	cp_codec_pixel_format_vdpau_mpeg1,///< mpeg-1 hw decoding with vdpau, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
	cp_codec_pixel_format_vdpau_mpeg2,///< mpeg-2 hw decoding with vdpau, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
	cp_codec_pixel_format_vdpau_wmv3,///< wmv3 hw decoding with vdpau, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
	cp_codec_pixel_format_vdpau_vc1, ///< vc-1 hw decoding with vdpau, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
#endif
	cp_codec_pixel_format_rgb48be,   ///< packed rgb 16:16:16, 48bpp, 16r, 16g, 16b, the 2-byte value for each r/g/b component is stored as big-endian
	cp_codec_pixel_format_rgb48le,   ///< packed rgb 16:16:16, 48bpp, 16r, 16g, 16b, the 2-byte value for each r/g/b component is stored as little-endian

	cp_codec_pixel_format_rgb565be,  ///< packed rgb 5:6:5, 16bpp, (msb)   5r 6g 5b(lsb), big-endian
	cp_codec_pixel_format_rgb565le,  ///< packed rgb 5:6:5, 16bpp, (msb)   5r 6g 5b(lsb), little-endian
	cp_codec_pixel_format_rgb555be,  ///< packed rgb 5:5:5, 16bpp, (msb)1x 5r 5g 5b(lsb), big-endian   , x=unused/undefined
	cp_codec_pixel_format_rgb555le,  ///< packed rgb 5:5:5, 16bpp, (msb)1x 5r 5g 5b(lsb), little-endian, x=unused/undefined

	cp_codec_pixel_format_bgr565be,  ///< packed bgr 5:6:5, 16bpp, (msb)   5b 6g 5r(lsb), big-endian
	cp_codec_pixel_format_bgr565le,  ///< packed bgr 5:6:5, 16bpp, (msb)   5b 6g 5r(lsb), little-endian
	cp_codec_pixel_format_bgr555be,  ///< packed bgr 5:5:5, 16bpp, (msb)1x 5b 5g 5r(lsb), big-endian   , x=unused/undefined
	cp_codec_pixel_format_bgr555le,  ///< packed bgr 5:5:5, 16bpp, (msb)1x 5b 5g 5r(lsb), little-endian, x=unused/undefined

#if ff_api_vaapi
	/** @name deprecated pixel formats */
	/**@{*/
	cp_codec_pixel_format_vaapi_moco, ///< hw acceleration through va api at motion compensation entry-point, picture.data[3] contains a vaapi_render_state struct which contains macroblocks as well as various fields extracted from headers
	cp_codec_pixel_format_vaapi_idct, ///< hw acceleration through va api at idct entry-point, picture.data[3] contains a vaapi_render_state struct which contains fields extracted from headers
	cp_codec_pixel_format_vaapi_vld,  ///< hw decoding through va api, picture.data[3] contains a vasurfaceid
	/**@}*/
	cp_codec_pixel_format_vaapi = cp_codec_pixel_format_vaapi_vld,
#else
	/**
	*  hardware acceleration through va-api, data[3] contains a
	*  vasurfaceid.
	*/
	cp_codec_pixel_format_vaapi,
#endif

	cp_codec_pixel_format_yuv420p16le,  ///< planar yuv 4:2:0, 24bpp, (1 cr & cb sample per 2x2 y samples), little-endian
	cp_codec_pixel_format_yuv420p16be,  ///< planar yuv 4:2:0, 24bpp, (1 cr & cb sample per 2x2 y samples), big-endian
	cp_codec_pixel_format_yuv422p16le,  ///< planar yuv 4:2:2, 32bpp, (1 cr & cb sample per 2x1 y samples), little-endian
	cp_codec_pixel_format_yuv422p16be,  ///< planar yuv 4:2:2, 32bpp, (1 cr & cb sample per 2x1 y samples), big-endian
	cp_codec_pixel_format_yuv444p16le,  ///< planar yuv 4:4:4, 48bpp, (1 cr & cb sample per 1x1 y samples), little-endian
	cp_codec_pixel_format_yuv444p16be,  ///< planar yuv 4:4:4, 48bpp, (1 cr & cb sample per 1x1 y samples), big-endian
#if ff_api_vdpau
	cp_codec_pixel_format_vdpau_mpeg4,  ///< mpeg-4 hw decoding with vdpau, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
#endif
	cp_codec_pixel_format_dxva2_vld,    ///< hw decoding through dxva2, picture.data[3] contains a lpdirect3dsurface9 pointer

	cp_codec_pixel_format_rgb444le,  ///< packed rgb 4:4:4, 16bpp, (msb)4x 4r 4g 4b(lsb), little-endian, x=unused/undefined
	cp_codec_pixel_format_rgb444be,  ///< packed rgb 4:4:4, 16bpp, (msb)4x 4r 4g 4b(lsb), big-endian,    x=unused/undefined
	cp_codec_pixel_format_bgr444le,  ///< packed bgr 4:4:4, 16bpp, (msb)4x 4b 4g 4r(lsb), little-endian, x=unused/undefined
	cp_codec_pixel_format_bgr444be,  ///< packed bgr 4:4:4, 16bpp, (msb)4x 4b 4g 4r(lsb), big-endian,    x=unused/undefined
	cp_codec_pixel_format_ya8,       ///< 8 bits gray, 8 bits alpha

	cp_codec_pixel_format_y400a = cp_codec_pixel_format_ya8, ///< alias for cp_codec_pixel_format_ya8
	cp_codec_pixel_format_gray8a = cp_codec_pixel_format_ya8, ///< alias for cp_codec_pixel_format_ya8

	cp_codec_pixel_format_bgr48be,   ///< packed rgb 16:16:16, 48bpp, 16b, 16g, 16r, the 2-byte value for each r/g/b component is stored as big-endian
	cp_codec_pixel_format_bgr48le,   ///< packed rgb 16:16:16, 48bpp, 16b, 16g, 16r, the 2-byte value for each r/g/b component is stored as little-endian

	/**
	* the following 12 formats have the disadvantage of needing 1 format for each bit depth.
	* notice that each 9/10 bits sample is stored in 16 bits with extra padding.
	* if you want to support multiple bit depths, then using cp_codec_pixel_format_yuv420p16* with the bpp stored separately is better.
	*/
	cp_codec_pixel_format_yuv420p9be, ///< planar yuv 4:2:0, 13.5bpp, (1 cr & cb sample per 2x2 y samples), big-endian
	cp_codec_pixel_format_yuv420p9le, ///< planar yuv 4:2:0, 13.5bpp, (1 cr & cb sample per 2x2 y samples), little-endian
	cp_codec_pixel_format_yuv420p10be,///< planar yuv 4:2:0, 15bpp, (1 cr & cb sample per 2x2 y samples), big-endian
	cp_codec_pixel_format_yuv420p10le,///< planar yuv 4:2:0, 15bpp, (1 cr & cb sample per 2x2 y samples), little-endian
	cp_codec_pixel_format_yuv422p10be,///< planar yuv 4:2:2, 20bpp, (1 cr & cb sample per 2x1 y samples), big-endian
	cp_codec_pixel_format_yuv422p10le,///< planar yuv 4:2:2, 20bpp, (1 cr & cb sample per 2x1 y samples), little-endian
	cp_codec_pixel_format_yuv444p9be, ///< planar yuv 4:4:4, 27bpp, (1 cr & cb sample per 1x1 y samples), big-endian
	cp_codec_pixel_format_yuv444p9le, ///< planar yuv 4:4:4, 27bpp, (1 cr & cb sample per 1x1 y samples), little-endian
	cp_codec_pixel_format_yuv444p10be,///< planar yuv 4:4:4, 30bpp, (1 cr & cb sample per 1x1 y samples), big-endian
	cp_codec_pixel_format_yuv444p10le,///< planar yuv 4:4:4, 30bpp, (1 cr & cb sample per 1x1 y samples), little-endian
	cp_codec_pixel_format_yuv422p9be, ///< planar yuv 4:2:2, 18bpp, (1 cr & cb sample per 2x1 y samples), big-endian
	cp_codec_pixel_format_yuv422p9le, ///< planar yuv 4:2:2, 18bpp, (1 cr & cb sample per 2x1 y samples), little-endian
	cp_codec_pixel_format_vda_vld,    ///< hardware decoding through vda
	cp_codec_pixel_format_gbrp,      ///< planar gbr 4:4:4 24bpp
	cp_codec_pixel_format_gbr24p = cp_codec_pixel_format_gbrp, // alias for #cp_codec_pixel_format_gbrp
	cp_codec_pixel_format_gbrp9be,   ///< planar gbr 4:4:4 27bpp, big-endian
	cp_codec_pixel_format_gbrp9le,   ///< planar gbr 4:4:4 27bpp, little-endian
	cp_codec_pixel_format_gbrp10be,  ///< planar gbr 4:4:4 30bpp, big-endian
	cp_codec_pixel_format_gbrp10le,  ///< planar gbr 4:4:4 30bpp, little-endian
	cp_codec_pixel_format_gbrp16be,  ///< planar gbr 4:4:4 48bpp, big-endian
	cp_codec_pixel_format_gbrp16le,  ///< planar gbr 4:4:4 48bpp, little-endian
	cp_codec_pixel_format_yuva422p,  ///< planar yuv 4:2:2 24bpp, (1 cr & cb sample per 2x1 y & a samples)
	cp_codec_pixel_format_yuva444p,  ///< planar yuv 4:4:4 32bpp, (1 cr & cb sample per 1x1 y & a samples)
	cp_codec_pixel_format_yuva420p9be,  ///< planar yuv 4:2:0 22.5bpp, (1 cr & cb sample per 2x2 y & a samples), big-endian
	cp_codec_pixel_format_yuva420p9le,  ///< planar yuv 4:2:0 22.5bpp, (1 cr & cb sample per 2x2 y & a samples), little-endian
	cp_codec_pixel_format_yuva422p9be,  ///< planar yuv 4:2:2 27bpp, (1 cr & cb sample per 2x1 y & a samples), big-endian
	cp_codec_pixel_format_yuva422p9le,  ///< planar yuv 4:2:2 27bpp, (1 cr & cb sample per 2x1 y & a samples), little-endian
	cp_codec_pixel_format_yuva444p9be,  ///< planar yuv 4:4:4 36bpp, (1 cr & cb sample per 1x1 y & a samples), big-endian
	cp_codec_pixel_format_yuva444p9le,  ///< planar yuv 4:4:4 36bpp, (1 cr & cb sample per 1x1 y & a samples), little-endian
	cp_codec_pixel_format_yuva420p10be, ///< planar yuv 4:2:0 25bpp, (1 cr & cb sample per 2x2 y & a samples, big-endian)
	cp_codec_pixel_format_yuva420p10le, ///< planar yuv 4:2:0 25bpp, (1 cr & cb sample per 2x2 y & a samples, little-endian)
	cp_codec_pixel_format_yuva422p10be, ///< planar yuv 4:2:2 30bpp, (1 cr & cb sample per 2x1 y & a samples, big-endian)
	cp_codec_pixel_format_yuva422p10le, ///< planar yuv 4:2:2 30bpp, (1 cr & cb sample per 2x1 y & a samples, little-endian)
	cp_codec_pixel_format_yuva444p10be, ///< planar yuv 4:4:4 40bpp, (1 cr & cb sample per 1x1 y & a samples, big-endian)
	cp_codec_pixel_format_yuva444p10le, ///< planar yuv 4:4:4 40bpp, (1 cr & cb sample per 1x1 y & a samples, little-endian)
	cp_codec_pixel_format_yuva420p16be, ///< planar yuv 4:2:0 40bpp, (1 cr & cb sample per 2x2 y & a samples, big-endian)
	cp_codec_pixel_format_yuva420p16le, ///< planar yuv 4:2:0 40bpp, (1 cr & cb sample per 2x2 y & a samples, little-endian)
	cp_codec_pixel_format_yuva422p16be, ///< planar yuv 4:2:2 48bpp, (1 cr & cb sample per 2x1 y & a samples, big-endian)
	cp_codec_pixel_format_yuva422p16le, ///< planar yuv 4:2:2 48bpp, (1 cr & cb sample per 2x1 y & a samples, little-endian)
	cp_codec_pixel_format_yuva444p16be, ///< planar yuv 4:4:4 64bpp, (1 cr & cb sample per 1x1 y & a samples, big-endian)
	cp_codec_pixel_format_yuva444p16le, ///< planar yuv 4:4:4 64bpp, (1 cr & cb sample per 1x1 y & a samples, little-endian)

	cp_codec_pixel_format_vdpau,     ///< hw acceleration through vdpau, picture.data[3] contains a vdpvideosurface

	cp_codec_pixel_format_xyz12le,      ///< packed xyz 4:4:4, 36 bpp, (msb) 12x, 12y, 12z (lsb), the 2-byte value for each x/y/z is stored as little-endian, the 4 lower bits are set to 0
	cp_codec_pixel_format_xyz12be,      ///< packed xyz 4:4:4, 36 bpp, (msb) 12x, 12y, 12z (lsb), the 2-byte value for each x/y/z is stored as big-endian, the 4 lower bits are set to 0
	cp_codec_pixel_format_nv16,         ///< interleaved chroma yuv 4:2:2, 16bpp, (1 cr & cb sample per 2x1 y samples)
	cp_codec_pixel_format_nv20le,       ///< interleaved chroma yuv 4:2:2, 20bpp, (1 cr & cb sample per 2x1 y samples), little-endian
	cp_codec_pixel_format_nv20be,       ///< interleaved chroma yuv 4:2:2, 20bpp, (1 cr & cb sample per 2x1 y samples), big-endian

	cp_codec_pixel_format_rgba64be,     ///< packed rgba 16:16:16:16, 64bpp, 16r, 16g, 16b, 16a, the 2-byte value for each r/g/b/a component is stored as big-endian
	cp_codec_pixel_format_rgba64le,     ///< packed rgba 16:16:16:16, 64bpp, 16r, 16g, 16b, 16a, the 2-byte value for each r/g/b/a component is stored as little-endian
	cp_codec_pixel_format_bgra64be,     ///< packed rgba 16:16:16:16, 64bpp, 16b, 16g, 16r, 16a, the 2-byte value for each r/g/b/a component is stored as big-endian
	cp_codec_pixel_format_bgra64le,     ///< packed rgba 16:16:16:16, 64bpp, 16b, 16g, 16r, 16a, the 2-byte value for each r/g/b/a component is stored as little-endian

	cp_codec_pixel_format_yvyu422,   ///< packed yuv 4:2:2, 16bpp, y0 cr y1 cb

	cp_codec_pixel_format_vda,          ///< hw acceleration through vda, data[3] contains a cvpixelbufferref

	cp_codec_pixel_format_ya16be,       ///< 16 bits gray, 16 bits alpha (big-endian)
	cp_codec_pixel_format_ya16le,       ///< 16 bits gray, 16 bits alpha (little-endian)

	cp_codec_pixel_format_gbrap,        ///< planar gbra 4:4:4:4 32bpp
	cp_codec_pixel_format_gbrap16be,    ///< planar gbra 4:4:4:4 64bpp, big-endian
	cp_codec_pixel_format_gbrap16le,    ///< planar gbra 4:4:4:4 64bpp, little-endian
	/**
	*  hw acceleration through qsv, data[3] contains a pointer to the
	*  mfxframesurface1 structure.
	*/
	cp_codec_pixel_format_qsv,
	/**
	* hw acceleration though mmal, data[3] contains a pointer to the
	* mmal_buffer_header_t structure.
	*/
	cp_codec_pixel_format_mmal,

	cp_codec_pixel_format_d3d11va_vld,  ///< hw decoding through direct3d11, picture.data[3] contains a id3d11videodecoderoutputview pointer

	/**
	* hw acceleration through cuda. data[i] contain cudeviceptr pointers
	* exactly as for system memory frames.
	*/
	cp_codec_pixel_format_cuda,

	cp_codec_pixel_format_0rgb = 0x123 + 4,///< packed rgb 8:8:8, 32bpp, xrgbxrgb...   x=unused/undefined
	cp_codec_pixel_format_rgb0,        ///< packed rgb 8:8:8, 32bpp, rgbxrgbx...   x=unused/undefined
	cp_codec_pixel_format_0bgr,        ///< packed bgr 8:8:8, 32bpp, xbgrxbgr...   x=unused/undefined
	cp_codec_pixel_format_bgr0,        ///< packed bgr 8:8:8, 32bpp, bgrxbgrx...   x=unused/undefined

	cp_codec_pixel_format_yuv420p12be, ///< planar yuv 4:2:0,18bpp, (1 cr & cb sample per 2x2 y samples), big-endian
	cp_codec_pixel_format_yuv420p12le, ///< planar yuv 4:2:0,18bpp, (1 cr & cb sample per 2x2 y samples), little-endian
	cp_codec_pixel_format_yuv420p14be, ///< planar yuv 4:2:0,21bpp, (1 cr & cb sample per 2x2 y samples), big-endian
	cp_codec_pixel_format_yuv420p14le, ///< planar yuv 4:2:0,21bpp, (1 cr & cb sample per 2x2 y samples), little-endian
	cp_codec_pixel_format_yuv422p12be, ///< planar yuv 4:2:2,24bpp, (1 cr & cb sample per 2x1 y samples), big-endian
	cp_codec_pixel_format_yuv422p12le, ///< planar yuv 4:2:2,24bpp, (1 cr & cb sample per 2x1 y samples), little-endian
	cp_codec_pixel_format_yuv422p14be, ///< planar yuv 4:2:2,28bpp, (1 cr & cb sample per 2x1 y samples), big-endian
	cp_codec_pixel_format_yuv422p14le, ///< planar yuv 4:2:2,28bpp, (1 cr & cb sample per 2x1 y samples), little-endian
	cp_codec_pixel_format_yuv444p12be, ///< planar yuv 4:4:4,36bpp, (1 cr & cb sample per 1x1 y samples), big-endian
	cp_codec_pixel_format_yuv444p12le, ///< planar yuv 4:4:4,36bpp, (1 cr & cb sample per 1x1 y samples), little-endian
	cp_codec_pixel_format_yuv444p14be, ///< planar yuv 4:4:4,42bpp, (1 cr & cb sample per 1x1 y samples), big-endian
	cp_codec_pixel_format_yuv444p14le, ///< planar yuv 4:4:4,42bpp, (1 cr & cb sample per 1x1 y samples), little-endian
	cp_codec_pixel_format_gbrp12be,    ///< planar gbr 4:4:4 36bpp, big-endian
	cp_codec_pixel_format_gbrp12le,    ///< planar gbr 4:4:4 36bpp, little-endian
	cp_codec_pixel_format_gbrp14be,    ///< planar gbr 4:4:4 42bpp, big-endian
	cp_codec_pixel_format_gbrp14le,    ///< planar gbr 4:4:4 42bpp, little-endian
	cp_codec_pixel_format_yuvj411p,    ///< planar yuv 4:1:1, 12bpp, (1 cr & cb sample per 4x1 y samples) full scale (jpeg), deprecated in favor of cp_codec_pixel_format_yuv411p and setting color_range

	cp_codec_pixel_format_bayer_bggr8,    ///< bayer, bgbg..(odd line), grgr..(even line), 8-bit samples */
	cp_codec_pixel_format_bayer_rggb8,    ///< bayer, rgrg..(odd line), gbgb..(even line), 8-bit samples */
	cp_codec_pixel_format_bayer_gbrg8,    ///< bayer, gbgb..(odd line), rgrg..(even line), 8-bit samples */
	cp_codec_pixel_format_bayer_grbg8,    ///< bayer, grgr..(odd line), bgbg..(even line), 8-bit samples */
	cp_codec_pixel_format_bayer_bggr16le, ///< bayer, bgbg..(odd line), grgr..(even line), 16-bit samples, little-endian */
	cp_codec_pixel_format_bayer_bggr16be, ///< bayer, bgbg..(odd line), grgr..(even line), 16-bit samples, big-endian */
	cp_codec_pixel_format_bayer_rggb16le, ///< bayer, rgrg..(odd line), gbgb..(even line), 16-bit samples, little-endian */
	cp_codec_pixel_format_bayer_rggb16be, ///< bayer, rgrg..(odd line), gbgb..(even line), 16-bit samples, big-endian */
	cp_codec_pixel_format_bayer_gbrg16le, ///< bayer, gbgb..(odd line), rgrg..(even line), 16-bit samples, little-endian */
	cp_codec_pixel_format_bayer_gbrg16be, ///< bayer, gbgb..(odd line), rgrg..(even line), 16-bit samples, big-endian */
	cp_codec_pixel_format_bayer_grbg16le, ///< bayer, grgr..(odd line), bgbg..(even line), 16-bit samples, little-endian */
	cp_codec_pixel_format_bayer_grbg16be, ///< bayer, grgr..(odd line), bgbg..(even line), 16-bit samples, big-endian */
#if !ff_api_xvmc
	cp_codec_pixel_format_xvmc,///< xvideo motion acceleration via common packet passing
#endif /* !ff_api_xvmc */
	cp_codec_pixel_format_yuv440p10le, ///< planar yuv 4:4:0,20bpp, (1 cr & cb sample per 1x2 y samples), little-endian
	cp_codec_pixel_format_yuv440p10be, ///< planar yuv 4:4:0,20bpp, (1 cr & cb sample per 1x2 y samples), big-endian
	cp_codec_pixel_format_yuv440p12le, ///< planar yuv 4:4:0,24bpp, (1 cr & cb sample per 1x2 y samples), little-endian
	cp_codec_pixel_format_yuv440p12be, ///< planar yuv 4:4:0,24bpp, (1 cr & cb sample per 1x2 y samples), big-endian
	cp_codec_pixel_format_ayuv64le,    ///< packed ayuv 4:4:4,64bpp (1 cr & cb sample per 1x1 y & a samples), little-endian
	cp_codec_pixel_format_ayuv64be,    ///< packed ayuv 4:4:4,64bpp (1 cr & cb sample per 1x1 y & a samples), big-endian

	cp_codec_pixel_format_videotoolbox, ///< hardware decoding through videotoolbox

	cp_codec_pixel_format_p010le, ///< like nv12, with 10bpp per component, data in the high bits, zeros in the low bits, little-endian
	cp_codec_pixel_format_p010be, ///< like nv12, with 10bpp per component, data in the high bits, zeros in the low bits, big-endian

	cp_codec_pixel_format_gbrap12be,  ///< planar gbr 4:4:4:4 48bpp, big-endian
	cp_codec_pixel_format_gbrap12le,  ///< planar gbr 4:4:4:4 48bpp, little-endian

	cp_codec_pixel_format_gbrap10be,  ///< planar gbr 4:4:4:4 40bpp, big-endian
	cp_codec_pixel_format_gbrap10le,  ///< planar gbr 4:4:4:4 40bpp, little-endian

	cp_codec_pixel_format_mediacodec, ///< hardware decoding through mediacodec

	cp_codec_pixel_format_nb         ///< number of pixel formats, do not use this if you want to link with shared libav* because the number of formats might differ between versions
}cp_codec_pixel_format_e;

#pragma pack()


#endif

