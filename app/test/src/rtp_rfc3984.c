/********************************************************************************
*
*             Copyright (C) 2007-2008 by Ingenient Technologies, Inc.
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
*  Filename: rtp_rfc3984.c
*
*  Author: Joseph (SB.CHO)
*
*  Description: RTP Payload Format for H.264 Video Streams as per RFC3984.
*
*  Module Description: Definitions and Function for Creating and Parsing
*      H.264 Payload Header in the Video Packets.
*
*  @version  $Revision: 1.6 $
*
********************************************************************************/

#include <stream_debug.h>

#include <rtp.h>

#include <rtp_rfc3984.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <netinet/in.h>

#ifndef RTP_RFC3984_PRINT_PAYLOAD_HEADER_ENABLED
#define RTP_RFC3984_PRINT_PAYLOAD_HEADER_ENABLED 0
#endif

static const char * pname = "RTP_RFC3984:";

static int size_checked = 0;

static void check_size(void)
{
    assert(sizeof(uint8_t) == 1);
    assert(sizeof(uint16_t) == 2);
    assert(sizeof(uint32_t) == 4);
    size_checked = 1;
}

typedef union {
    uint16_t u16;
    uint8_t u8[2];
} u16_union;

typedef union {
    uint32_t u32;
    uint8_t u8[4];
} u32_union;

/* Store a Host Ordered 16-bit value in an unaligned buffer in
   Network Byte Order. */
static void set_buffer_u16_hton(uint8_t * buffer, uint16_t hbo_value)
{
    u16_union nbo_value;
    if (!size_checked)
        check_size();
    nbo_value.u16 = htons(hbo_value);
    buffer[0] = nbo_value.u8[0];
    buffer[1] = nbo_value.u8[1];
}

/* Store a Host Ordered 32-bit value in an unaligned buffer in
   Network Byte Order. */
static void set_buffer_u32_hton(uint8_t * buffer, uint32_t hbo_value)
{
    u32_union nbo_value;
    if (!size_checked)
        check_size();
    nbo_value.u32 = htonl(hbo_value);
    buffer[0] = nbo_value.u8[0];
    buffer[1] = nbo_value.u8[1];
    buffer[2] = nbo_value.u8[2];
    buffer[3] = nbo_value.u8[3];
}

/* Retrieve a Host Ordered 16-bit value from an unaligned buffer in
   Network Byte Order. */
static uint16_t get_buffer_u16_ntoh(const uint8_t * buffer)
{
    u16_union u16u;
    if (!size_checked)
        check_size();
    u16u.u8[0] = buffer[0];
    u16u.u8[1] = buffer[1];
    return htons(u16u.u16);
}

/* Retrieve a Host Ordered 32-bit value from an unaligned buffer in
   Network Byte Order. */
static uint32_t get_buffer_u32_ntoh(const uint8_t * buffer)
{
    u32_union u32u;
    if (!size_checked)
        check_size();
    u32u.u8[0] = buffer[0];
    u32u.u8[1] = buffer[1];
    u32u.u8[2] = buffer[2];
    u32u.u8[3] = buffer[3];
    return htonl(u32u.u32);
}

int rtp_rfc3984_get_h264_params(struct rtp_rfc3984_h264params * param,
        const void * h264_frame, size_t h264_len, size_t max_size, int header_size)
{
    uint32_t i = 0;
    uint8_t * frame = (uint8_t *)h264_frame;
    uint8_t nal_type;

    memset(param, 0, sizeof(struct rtp_rfc3984_h264params));
    for (i = 0; i < h264_len; i++)
    {
        if (frame[i] == 0)
        {
            continue;
        } else if (frame[i] == 1 && i == 3)
        {
            nal_type = frame[i + 1] & 0x1f;
            if (nal_type >= 1 && nal_type <= 23) // Single NAL unit type
            {
                param->nal_unit = frame[i + 1];
                if (h264_len - i <= max_size - header_size)
                {
                    param->fragmented = 0;
                } else
                {
                   param->fragmented = 1;
                   param->fu_indicator = (param->nal_unit & 0x60) | 28;
                   param->fu_header = (param->nal_unit & 0x1f) | 0x80;
                }
                return 0;
            } else // No single NAL unit type
            {
                DEBUG_SAY("%s Not supported NAL unit type: %d\n",
                        pname, nal_type);
                return -1;
            }
        }
    }

    return -1;
}

#define RTP_HDR_SIZE 12

int rtp_rfc3984_build_packet(void * rtp_buffer, size_t rtp_buffer_size,
        size_t * rtp_packet_size, const rtp_build_t * rtp_build,
        const void * payload, size_t payload_size,
        struct rtp_rfc3984_h264params * h264_info)
{
    unsigned char * srcdata = (unsigned char *)payload;
    unsigned char * rtp_header = (unsigned char *)rtp_buffer;
    unsigned char * h264_header;
    unsigned char * h264_data;
    int i = 0, datasize = 0;
    uint8_t csrccnt = 0;
    uint8_t * rtp_csrc = NULL;
    uint8_t * rtp_extension = NULL;
    uint8_t * rtp_body = NULL;
    size_t header_size = RTP_HDR_SIZE; /* Header Size. */

    /* RTP Header can contain at most 15 CSRCs according to the RFC. */
    if (rtp_build->csrccnt > 0 && rtp_build->csrc != NULL)
    {
        csrccnt = (rtp_build->csrccnt <= 15) ? rtp_build->csrccnt : 15;
        rtp_csrc = rtp_header + header_size;
        header_size += csrccnt * 4;
    }

    /* RTP Header Extension . */
    if (rtp_build->extensionflag == RTP_FLAG_ON)
    {
        rtp_extension = rtp_header + header_size;
        header_size += 4;
        if (rtp_build->extensioncnt > 0 && rtp_build->extensiondata != NULL)
            header_size += rtp_build->extensioncnt * 4;
    }

    memset(rtp_header, 0, header_size);

    rtp_body = rtp_header + header_size;

    h264_header = (unsigned char *)rtp_buffer + header_size;

    h264_data = (unsigned char *) (rtp_buffer + header_size
	         + (h264_info->fragmented == 0 ? 0: 2));


    /* RTP version */
    rtp_header[0] |= (rtp_build->version << 6) & 0xC0;

//#warning "FIXME: Padding Not Supported."
#if 0
    /* Padding Bit. */
    if (rtp_build->paddingcnt > 0)
        rtp_header[0] |= 0x20;
#endif

    /* Extension Bit. */
    if (rtp_build->extensionflag == RTP_FLAG_ON)
        rtp_header[0] |= 0x10;

    /* CSRC Count. */
    rtp_header[0] |= csrccnt & 0x0F;

    /* Marker Bit. */
    if (rtp_build->marker == RTP_FLAG_ON)
        rtp_set_marker_flag(rtp_header);

    /* Payload Type. */
    rtp_header[1] |= rtp_build->payloadtype & 0x7F;
    rtp_header[1] &= 0x7F;

    /* Sequence Number. */
    set_buffer_u16_hton(&rtp_header[2], rtp_build->sequencenumber);

    /* TimeStamp. */
    set_buffer_u32_hton(&rtp_header[4], rtp_build->timestamp);

    /* SSRC. */
    set_buffer_u32_hton(&rtp_header[8], rtp_build->ssrc);

    /* CSRC. */
    if (rtp_csrc != NULL)
    {
        for (i = 0; i < csrccnt; i++)
        {
            set_buffer_u32_hton(&rtp_csrc[i * 4], rtp_build->csrc[i]);
        }
    }

    datasize = rtp_buffer_size - header_size
            - (h264_info->fragmented == 0 ? 0 : 2);
    if (payload_size <= datasize)
    {
        datasize = payload_size;
        rtp_header[1] |= 0x80; // set marker bit
        if (h264_info->fragmented)
        {
            h264_info->fu_header = h264_info->fu_header & 0x7F; //start bit clear
            h264_info->fu_header = h264_info->fu_header | 0x40; //end bit set
        }
    } 
    *rtp_packet_size = datasize + header_size
            + (h264_info->fragmented == 0 ? 0 : 2);
    if (h264_info->fragmented)
    {
        h264_header[0] = h264_info->fu_indicator;
        h264_header[1] = h264_info->fu_header;
        // clear start and end bit
        h264_info->fu_header = h264_info->fu_header & 0x1f;
    }
    memcpy(h264_data, srcdata, datasize);  

    return datasize;
}

int rtp_rfc3984_skip_startcode(uint8_t * bs, uint32_t size)
{
    int i, offset = 0;
    
    for (i = 0; i < size - 3; i++)
    {
        if ((bs[i] == 0) & (bs[i+1] == 0) && (bs[i+2] == 0x01))
        {
            offset = i+3;
            break;
        }
    }
    
    return offset;
}

int rtp_rfc3984_build_packet2(void * rtp_buffer, size_t rtp_buffer_size,
        size_t * rtp_packet_size, const rtp_build_t * rtp_build,
        struct rtp_bitstream_packetization_info * bspacket_info)
{
    int i;
    uint8_t * rtp_packet = (uint8_t *)rtp_buffer;
    uint32_t csrccnt = 0;
    uint8_t * bspacket;
    uint32_t num_packets, * packet_offsets = bspacket_info->packet_offsets;
    uint32_t last_bspacket = 0, bspacket_index, bspacket_size, bsoffset;
    
    /* RTP version */
    *rtp_packet = (rtp_build->version << 6) & 0xc0;
    
    /* CSRC count */
    if (rtp_build->csrccnt > 0 && rtp_build->csrc != NULL)
        csrccnt = (rtp_build->csrccnt <= 15) ? rtp_build->csrccnt : 15;

    *rtp_packet++ |= csrccnt & 0x0f;
    
    num_packets = * packet_offsets;
    bspacket_index = bspacket_info->cur_packet++;

    if (bspacket_index >= num_packets - 1)
    {
        last_bspacket = 1;
        *rtp_packet = 0x80;
    } else
    {
        *rtp_packet = 0x00;
    }

    /* Payload Type */
    *rtp_packet++ |= rtp_build->payloadtype & 0x7f;
    
    /** Sequence Number */
    set_buffer_u16_hton(rtp_packet, rtp_build->sequencenumber);
    rtp_packet += 2;
    
    /** TimeStamp */
    set_buffer_u32_hton(rtp_packet, rtp_build->timestamp);
    rtp_packet += 4;
    
    /** SSRC */
    set_buffer_u32_hton(rtp_packet, rtp_build->ssrc);
    rtp_packet += 4;
    
    /* CSRC */
    if (csrccnt > 0)
    {
        for (i = 0; i < csrccnt; i++)
        {
            set_buffer_u32_hton(rtp_packet, rtp_build->csrc[i]);
            rtp_packet += 4;
        }
    }        
    
    bspacket = bspacket_info->packets_start + 
            bspacket_info->packet_offsets[bspacket_index+1];

    if (last_bspacket == 0)
    {
        bspacket_size = 
            bspacket_info->packet_offsets[bspacket_index + 2] -
            bspacket_info->packet_offsets[bspacket_index + 1];
                
    } else
    {
        bspacket_size = 
            bspacket_info->packets_size - 
            bspacket_info->packet_offsets[bspacket_index + 1];
    }

    bsoffset = rtp_rfc3984_skip_startcode(bspacket, bspacket_size);

    memcpy(rtp_packet, bspacket + bsoffset, bspacket_size - bsoffset);

    *rtp_packet_size = rtp_packet + bspacket_size - bsoffset - (uint8_t *)rtp_buffer;

    return bspacket_size;    
}

int rtp_rfc3984_parse_packet(rtp_parse_t * rtp_parse,
        void * rtp_packet, size_t rtp_packet_size)
{
    uint8_t type, nal_unit;
    uint8_t * h264_data;

    if (rtp_packet_size < 12)
    {
        DEBUG_ERROR("%s RTP Packet Too Small.\n", pname);
        return -1;
    }

    rtp_parse_init(rtp_parse);
    rtp_parse->header = rtp_packet;
    rtp_parse->headersize = 12;
    rtp_parse->version = (rtp_parse->header[0] >> 6) & 0x03;
    if (rtp_parse->version != 2)
    {
        DEBUG_ERROR("%s Library Only Supports RTP Version 2.\n", pname);
        return -1;
    }
    rtp_parse->csrccnt = (rtp_parse->header[0] >> 0) & 0x0F;
    if (rtp_parse->csrccnt > 0)
    {
        rtp_parse->csrc = &rtp_parse->header[rtp_parse->headersize];
        rtp_parse->headersize += rtp_parse->csrccnt * 4;
    }
    if ((rtp_parse->header[1] >> 7) & 0x01)
        rtp_parse->marker = RTP_FLAG_ON;
    else
        rtp_parse->marker = RTP_FLAG_OFF;
    rtp_parse->payloadtype = (rtp_parse->header[1] >> 0) & 0x7F;
    rtp_parse->sequencenumber = get_buffer_u16_ntoh(&rtp_parse->header[2]);
    rtp_parse->timestamp = get_buffer_u32_ntoh(&rtp_parse->header[4]);
    rtp_parse->ssrc = get_buffer_u32_ntoh(&rtp_parse->header[8]);
    h264_data = &rtp_parse->header[rtp_parse->headersize];
    rtp_parse->payloadsize = 0;

    type = h264_data[0] & 0x1f;
    // 1 <= nal_type <= 23, Single NAL Unit
    if (type >= 1 && type <= 23)
        type = 1;
    switch (type)
    {
        case 1 : // 1 ~ 23, single nal unit
            rtp_parse->header[8] = 0x00;
            rtp_parse->header[9] = 0x00;
            rtp_parse->header[10] = 0x00;
            rtp_parse->header[11] = 0x01;
            rtp_parse->payload = &rtp_parse->header[8];
            rtp_parse->payloadsize = rtp_packet_size
                    - rtp_parse->headersize + 4;
            break;
        case 24 : // STAP-A
            DEBUG_ERROR("%s NALU : STAP-A Not Support Yet\n", pname);
            goto unsupported;
            break;
        case 25 : // STAP-B
            DEBUG_ERROR("%s NALU : STAP-B Not Support Yet\n", pname);
            goto unsupported;
            break;
        case 26 : // MTAP16
            DEBUG_ERROR("%s NALU : MTAP16 Not Support Yet\n", pname);
            goto unsupported;
            break;
        case 27 : // MTAP4
            DEBUG_ERROR("%s NALU : MTAP24 Not Support Yet\n", pname);
            goto unsupported;
            break;
        case 28 : // FU-A
            if (h264_data[1] & 0x80) // FU-A Start frame
            {
                nal_unit = (h264_data[0] & 0x60) | (h264_data[1] & 0x1f);
                rtp_parse->header[9] = 0x00;
                rtp_parse->header[10] = 0x00;
                rtp_parse->header[11] = 0x00;
                h264_data[0] = 0x01;
                h264_data[1] = nal_unit;
                rtp_parse->payload = &rtp_parse->header[9];
                rtp_parse->payloadsize = rtp_packet_size
                        - rtp_parse->headersize + 3;
            } else
            {
                rtp_parse->payload = &h264_data[2];
                rtp_parse->payloadsize = rtp_packet_size
                        - rtp_parse->headersize - 2;
            }
            break;
        case 29 : // FU-B
            DEBUG_ERROR("%s NALU : FU-B Not Support Yet\n", pname);
            goto unsupported;
            break;
        default :
            DEBUG_ERROR("%s NALU : NALU %d Not Support Yet\n", pname, type);
            goto unsupported;
            break;
    }
    return rtp_parse->payloadsize;

unsupported:
    DEBUG_ERROR("%s ", pname);
    {
        int i = 0;
        for (i = 0; i < rtp_parse->headersize; i++)
        {
            fprintf(DEBUG_ERROR_FILE, "%02x", rtp_parse->header[i]);
            if (i % 4 == 0)
                fprintf(DEBUG_ERROR_FILE, " ");
        }
    }
    fprintf(DEBUG_ERROR_FILE, "\n");
    return 0;
}
