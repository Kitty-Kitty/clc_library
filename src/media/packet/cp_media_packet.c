/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-05

Description:

**************************************************************************/

#include "cp_media_packet.h"


//创建一个media packet
cp_media_packet_t *create_media_packet(cp_pool_t *pool, cp_int32_t size, cp_media_packet_type_e type)
{
	return create_number_media_packet(pool, size, 1, type);
}

//创建多个media packet
cp_media_packet_t *create_number_media_packet(cp_pool_t *pool, cp_int32_t size, cp_int32_t number, cp_media_packet_type_e type)
{
	cp_int32_t						i = 0;
	cp_int32_t						j = 0;
	cp_void_t						*tmp_void_p = CP_NULL;
	cp_void_t						*tmp_buf_p = CP_NULL;
	cp_uchar_t						*tmp_root_buf_p = CP_NULL;
	cp_media_packet_t				*tmp_mp = CP_NULL;
	cp_media_packet_t				*tmp_root_mp = CP_NULL;



	if (!pool || !number) {
		return CP_NULL;
	}

	tmp_void_p = (cp_void_t*)cp_palloc(pool, (cp_sizeof(cp_media_packet_t) + size) * number);
	if (!tmp_void_p) {
		return CP_NULL;
	}
	cp_memset(tmp_void_p, 0, (cp_sizeof(cp_media_packet_t) + size) * number);
	tmp_root_mp = (cp_media_packet_t*)tmp_void_p;
	tmp_mp = tmp_root_mp;
	tmp_root_buf_p = ((cp_uchar_t*)tmp_void_p) + (cp_sizeof(cp_media_packet_t) * number);

	for (i = 0; i < number; i++, tmp_mp++) {
		tmp_mp->type = type;
		tmp_mp->pool = pool;

		for (j = 0; j < CP_MEDIA_PACKET_MAX_BUFFER_NUMBER; j++) {
			cp_buf_clear(&tmp_mp->mp_buf.buf[j]);
		}

		if (size) {
			tmp_buf_p = tmp_root_buf_p + size * i;
			cp_buf_assemble(&tmp_mp->mp_buf.buf[0], tmp_buf_p, size);
		}
	}
	
	return tmp_root_mp;
}

//获取媒体包数据长度
cp_int32_t get_media_packet_data_length(cp_media_packet_t *mp)
{
	cp_int32_t				i = 0;
	cp_int32_t				tmp_sum = 0;


	if (!mp) {
		return 0;
	}

	for (i = 0; i < CP_MEDIA_PACKET_MAX_BUFFER_NUMBER; i++) {
		tmp_sum += cp_buf_get_length(&mp->mp_buf.buf[i]);
	}
	return tmp_sum;
}

//清除media packet数据
cp_int32_t clear_media_packet(cp_media_packet_t *mp)
{
	cp_int32_t				i = 0;


	if (!mp) {
		return -1;
	}
	for (i = 0; i < CP_MEDIA_PACKET_MAX_BUFFER_NUMBER; i++) {
		cp_buf_clear(&mp->mp_buf.buf[i]);
	}

	return 0;
}

//创建指定通道
cp_int32_t create_media_packet_channel_buffer(cp_media_packet_t *mp, cp_int32_t channel_number, cp_int32_t size)
{
	cp_void_t						*tmp_p = CP_NULL;



	if (!mp || !mp->pool || channel_number < 0 || 
		channel_number > CP_MEDIA_PACKET_MAX_BUFFER_NUMBER || size < 0) {
		return -1;
	}
	tmp_p = (cp_void_t*)cp_palloc(mp->pool, size);
	if (!tmp_p) {
		return -2;
	}
	cp_buf_assemble(&mp->mp_buf.buf[channel_number], tmp_p, size);
	return 0;
}

//消毁一个media packet
cp_int32_t destroy_media_packet(cp_media_packet_t *mp)
{
	cp_int32_t						i = 0;



	if (!mp || !mp->pool) {
		return -1;
	}
	
	for (i = 0; i < CP_MEDIA_PACKET_MAX_BUFFER_NUMBER; i++) {
		if (cp_buf_get_size(&mp->mp_buf.buf[i])) {
			cp_pfree(mp->pool, cp_buf_get_start(&mp->mp_buf.buf[i]));
		}
	}

	cp_pfree(mp->pool, mp);
	return 0;
}

//创建媒体描述信息
cp_int32_t create_media_packet_description(cp_pool_t *pool, cp_media_packet_t *mp, cp_media_description_type_e type)
{
	if (!pool || !mp) {
		return -1;
	}
	mp->md_p = create_media_description(pool, type);
	if (!mp->md_p && type == cp_media_description_type_none) {
		return -2;
	}
	return 0;
}

//消毁媒体描述信息
cp_int32_t destroy_media_packet_description(cp_pool_t *pool, cp_media_packet_t *packet)
{
	cp_int32_t					tmp_ret_int = 0;



	if (!pool || !packet) {
		return -1;
	}
	if (packet->md_p) {
		tmp_ret_int = destroy_media_description(pool, packet->md_p);
		if (!tmp_ret_int) {
			packet->md_p = CP_NULL;
		}
		return tmp_ret_int;
	}
	
	return 0;
}