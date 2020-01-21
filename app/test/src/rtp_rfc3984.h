/********************************************************************************
*
*             Copyright (C) 2007 by Ingenient Technologies, Inc.
*                            All Rights Reserved.
*
*             This software is unpublished and contains the trade
*             secrets and confidential proprietary information of
*                          Ingenient Technologies.
*
*                             www.ingenient.com
*
*********************************************************************************
*
*  Filename: rtp_rfc3984.h
*
*  Author: Joseph (SBCHO)
*
*  Description: RTP Payload Format for H.264  Video Streams as per RFC3984.
*
*  Module Description: Definitions and Function for Creating and Parsing
*       MJPEG Payload Header in the Video Packets.
*
*  @version  $Revision: 1.3 $
*
********************************************************************************/

#ifndef RTP_RFC3984_H__
#define RTP_RFC3984_H__

#include <inttypes.h>

#include <rtp.h>

/**
 * @defgroup RTP_RFC3984 RTP Library - RTP Payload Format for H.264 Video Streams RFC-2190
 *
 * Creation and Parsing of RTP RFC-3984 Packets.
 */

/** @addtogroup RTP_RFC3984
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

struct rtp_bitstream_packetization_info {
    /** Packet start */
    uint8_t * packets_start;
    /** Packets size */
    uint32_t packets_size;
    /** Packet offsets */
    uint32_t * packet_offsets;
    /** Current packet */
    int cur_packet;
};

/** H.264 Params. */
struct rtp_rfc3984_h264params {
    /** nal unit octet
     *
     * @verbatim

        bit : 0 1 2 3 4 5 6 7 
        ---------------------
        val : F|NRI| type
        ----------------------
        F: 1bit, forbidden_zero_bit
        NRI: 2bits, nal_ref_idc
        type: 5bits, Type
        0 : undefined
        1-23 : NAL single unit
        24 : STAP-A
        25 : STAP-B
        26 : MTAP-16
        27 : MTAP-24
        28 : FU-A
        29 : FU-B
        30-31: undefined

       @endverbatim
     */
    uint8_t nal_unit;

    /** FU indicator octet
     *
     * @verbatim

        bit : 0 1 2 3 4 5 6 7
        ---------------------
        val : F|NRI| type
        ---------------------
        type = 28, FU-A (fixed, now support only FU-A)        
        NRI = from nal_unit

       @endverbatim
     */
    uint8_t fu_indicator;

    /** FU header octet
     *
     * @verbatim

        bit : 0 1 2 3 4 5 6 7
        ---------------------
        val : S|E|R| type
        ---------------------
        S : 1 bit, start bit
        E : 1 bit, end bit
        type = from nal_unit
        S & E exclusive

       @endverbatim
     */
    uint8_t fu_header;

    /**
     * Frame is Fragmented.
     *
     * if nal <= packet size fragmented = 0
     * else fragmented = 1
     * if (fragmented) fu_indicator and fu_header must be set.
     */
    uint8_t fragmented;
};

int rtp_rfc3984_get_h264_params(struct rtp_rfc3984_h264params * param,
        const void * h264_frame, size_t h264_len, size_t max_size, int header_size);

/**
 * RFC3984 RTP Packet Build.
 *
 * Build an RFC3984 RTP Packet.
 *
 * @param rtp_buffer Location of buffer in which to build the RTP Packet.
 * @param rtp_buffer_size Size of the buffer.
 * @param rtp_packet_size The size of the resulting RTP Packet is stored here.
 * @param rtp_build RTP Build Structure containing the desired header values.
 * @param payload Pointer to the Payload.
 * @param payload_size Payload size.
 *
 * @return Returns the number of bytes from the payload placed in the RTP Packet
 * (amount of the payload consumed) on success. Returns -1 on error.
 */
int rtp_rfc3984_build_packet(void * rtp_buffer, size_t rtp_buffer_size,
        size_t * rtp_packet_size, const rtp_build_t * rtp_build,
        const void * payload, size_t payload_size,
        struct rtp_rfc3984_h264params * h264_info);

/**
 *
 * Build an RFC3984 RTP Packet using DSP packetization info.
 *
 * @param rtp_buffer RTP Packet buffer.
 * @param rtp_buffer_size Size of the buffer.
 * @param rtp_packet_size The size of the resulting RTP Packet.
 * @param rtp_build RTP Build Structure containing the desired header values.
 *
 * @return Returns the number of bytes from the payload placed in the RTP Packet
 * (amount of the payload consumed) on success. Returns -1 on error.
 */
int rtp_rfc3984_build_packet2(void * rtp_buffer, size_t rtp_buffer_size,
        size_t * rtp_packet_size, const rtp_build_t * rtp_build,
        struct rtp_bitstream_packetization_info * packet_info);

/**
 * RFC3984 RTP Packet Parser.
 *
 * Parse an RTP Packet updating the RTP Parse Structure accordingly.
 *
 * @param rtp_parse RTP Parse Structure.
 * @param rtp_packet Buffer containing the RTP Packet.
 * @param rtp_packet_size Size of the RTP Packet.
 *
 * @return Returns the number of bytes in the RTP Packet Payload on success.
 * Returns -1 on error.
 */
int rtp_rfc3984_parse_packet(rtp_parse_t * rtp_parse,
        void * rtp_packet, size_t rtp_packet_size);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* RTP_RFC3984_H__ */
