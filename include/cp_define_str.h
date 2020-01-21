/**************************************************************************

* Copyright: tianhuiming@novigo.com.cn

* Author：tianhuiming@novigo.com.cn

* Date：2016-4-21 15:59:42

* Description:

**************************************************************************/
#ifndef _CP_APP_DEFINE_INCLUDE_H_
#define _CP_APP_DEFINE_INCLUDE_H_


////////////////////////////////HOST//////////////////////////////////////////
#define CP_APP_STR_HOST						"Host"
#define CP_APP_STR_ID						"ID"
#define CP_APP_STR_NAME						"Name"
#define CP_APP_STR_PASSWD					"Password"
#define CP_APP_STR_VERSION					"Version"
#define CP_APP_STR_TYPE						"Type"
#define CP_APP_STR_STATUS					"Status"
#define CP_APP_STR_NO						"No"

#define CP_APP_STR_USEDPASSWORD				"UsedPassword"

#define CP_APP_STR_CENTER					"Center"

#define CP_APP_STR_HEARTBEAT_TIMES			"HeartbeatTimes"
#define CP_APP_STR_HEARTBEAT_INTERVAL		"HeartbeatInterval"

/////////////////////////////////网络配置/////////////////////////////////////////
#define CP_APP_STR_INTERFACES				"Interfaces"
#define CP_APP_STR_INTERFACE				"Interface"
#define CP_APP_STR_USRD						"Used"
#define CP_APP_STR_IP						"IP"
#define CP_APP_STR_PORT						"Port"
#define CP_APP_STR_TCPPORT					"TCPPort"
#define CP_APP_STR_UDPPORT					"UDPPort"
#define CP_APP_STR_IN_NAME					"Eth0"
#define	CP_APP_STR_CHUNKSIZE				"ChunkSize"
#define CP_APP_STR_BOOTPROTOCOL				"BootProtocol"
#define CP_APP_STR_NETMASK					"NetMask"
#define CP_APP_STR_GATEWAY					"Gateway"
#define CP_APP_STR_NETWORKS					"Networks"


//////////////////////////////////硬件信息////////////////////////////////////////
#define CP_APP_STR_INFORMATION				"Information"
#define CP_APP_STR_NUMBER					"Number"
#define CP_APP_STR_LIMITDISK				"LimitDisk"
#define CP_APP_STR_LIMITMEMORY				"LimitMemory"
#define CP_APP_STR_LIMITCPU					"LimitCPU"
#define CP_APP_STR_LIMITNETWORK				"LimitNetWork"
#define CP_APP_STR_LIMITPLAYCOUNT			"LimitPlayCount"
#define CP_APP_STR_LIMITCONNECTION			"LimitConnect"
#define CP_APP_STR_RESOLUTION				"Resolution"
#define CP_APP_STR_WIDTH					"Width"
#define CP_APP_STR_HEIGHT					"Height"
#define CP_APP_STR_BACKCOLOR				"BackColor"
#define CP_APP_STR_BACKSIZE					"BackSize"
#define CP_APP_STR_SIZE						"Size"
#define CP_APP_STR_BORDER					"Border"
#define CP_APP_STR_LUMINANCE				"Luminance"
#define CP_APP_STR_CONTRAST					"Contrast"
#define CP_APP_STR_COLORTEMPERATURE			"ColorTemperature"
#define CP_APP_STR_SWITCH					"Switch"
#define CP_APP_STR_BACKGROUND				"Background"

#define CP_APP_STR_DISK						"Disk"
#define CP_APP_STR_MEMORY					"Memory"
#define CP_APP_STR_CPU						"CPU"
#define CP_APP_STR_NETWORK					"NetWork"
#define CP_APP_STR_PLAYCOUNT				"PlayCount"

#define CP_APP_STR_RESET					"Reset"

#define CP_APP_STR_CHECKCOLOR				"CheckColor"
#define CP_APP_STR_SOURCECOLOR				"source_color"
#define CP_APP_STR_DESTCOLOR				"dest_color"


////////////////////////////////状态返回//////////////////////////////////////////
#define CP_APP_STR_REASON					"Reason"
#define CP_APP_STR_RETURN					"Return"


////////////////////////////////异常上报//////////////////////////////////////////
#define CP_APP_STR_EXCEPTIONS				"Exceptions"
#define CP_APP_STR_EXCEPTION				"Exception"
#define CP_APP_STR_PRIVATE_STATUS			"PrivateStatus"
#define CP_APP_STR_DESCRIPTION				"Description"
#define CP_APP_STR_NO_EXCEPTION				"NO EXCEPTION"
#define CP_APP_STR_TIME						"Time"

////////////////////////////////媒体/////////////////////////////////////////////
#define CP_APP_STR_PLAYSESSION				"PlaySession"
#define CP_APP_STR_CHANNELID				"ChannelID"

////////////////////////////////串口/////////////////////////////////////////////
#define CP_APP_STR_SERIALS					"Serials"
#define CP_APP_STR_SERIAL					"Serial"
#define CP_APP_STR_BAUDRATE					"BaudRate"
#define CP_APP_STR_CHARACTER_SIZE			"CharacterSize"
#define CP_APP_STR_FLOW_CONTROL				"FlowControl"
#define CP_APP_STR_PARITY					"Parity"
#define CP_APP_STR_STOP_BITS				"StopBits"

/////////////////////////////软件更新功能使用的字符串/////////////////////////////////////////
#define	CP_APP_STR_PACKET_UPDATE			"Update"
#define	CP_APP_STR_PACKET_TYPE				"PacketType"
#define	CP_APP_STR_PACKET_NAME				"PacketName"
#define	CP_APP_STR_OPERATION_FLAG			"OperationFlag"
#define	CP_APP_STR_VERSION_ADDTION			"VersionAddtion"
#define	CP_APP_STR_TIME						"Time"
#define	CP_APP_STR_SERIAL_MASTER			"SerialMaster"
#define	CP_APP_STR_SERIAL_SLAVE				"SerialSlave"
#define	CP_APP_STR_PLATFORM_HARDWARE		"PlatformHardware"
#define	CP_APP_STR_PLATFORM_SOFTWARE		"PlatformSoftware"
#define	CP_APP_STR_CHANGER_LOG				"ChangerLog"
#define	CP_APP_STR_PROGRAM_FILE				"ProgramFile"

//////////////////////////////媒体播放通道的字符串////////////////////////////////////////////
#define	CP_APP_STR_PLAY_INFORMATION			"PlayInformation"
#define	CP_APP_STR_MEDIAS					"Medias"
#define	CP_APP_STR_MEDIA					"Media"
#define	CP_APP_STR_FLAG						"Flag"
#define	CP_APP_STR_PLAYSESSION				"PlaySession"
#define	CP_APP_STR_CHANNELID				"ChannelID"
#define	CP_APP_STR_GROUPID					"GroupID"
//视频信息
#define	CP_APP_STR_VIDEO_SOURCE				"VideoSource"
#define	CP_APP_STR_HEIGHT					"Height"
#define	CP_APP_STR_WIDTH					"Width"
#define	CP_APP_STR_FPS						"Fps"
//音频信息
#define	CP_APP_STR_AUDIO_SOURCE				"AudioSource"
#define	CP_APP_STR_BIT_RATE					"BitRate"
#define	CP_APP_STR_SAMPLE_RATE				"SampleRate"
#define	CP_APP_STR_SOUND_CHANNEL_NAME		"SoundChannelName"
#define	CP_APP_STR_SOUND_CHANNEL_TYPE		"SoundChannelType"
#define	CP_APP_STR_VOLUME					"Volume"

#define	CP_APP_STR_ADDR						"Addr"
#define	CP_APP_STR_LAYER					"Layer"
#define	CP_APP_STR_POSITION					"Position"
#define	CP_APP_STR_MULTICAST				"Multicast"
#define	CP_APP_STR_PLAYADDRESS				"PlayAddress"
#define	CP_APP_STR_STREAM_DESCRIPTION		"StreamDescription"
#define	CP_APP_STR_DISTRIBUTION_TYPE		"DistributionType"
#define	CP_APP_STR_TRANSPORT_TYPE			"TransportType"

#define CP_APP_STR_ENCODE_TYPE				"EncodeType"
#define CP_APP_STR_ENCODE_NAME				"EncodeName"

#define CP_APP_STR_DEVICES					"Devices"
#define CP_APP_STR_DEVICE					"Device"
#define	CP_APP_STR_CHANNELS					"Channels"
#define	CP_APP_STR_CHANNEL					"Channel"

#define CP_APP_STR_GROUPS					"Groups"
#define CP_APP_STR_GROUP					"Group"
#define CP_APP_STR_COMMANDTIME				"CommandTime"
#define CP_APP_STR_SEQUENCENUMBER			"SequenceNumber"

///////////////////////////////同步信息///////////////////////////////////////////
#define CP_PLYAER_STR_SYNCINFORMATION		"SyncInformation"
#define CP_PLYAER_STR_TIMESTAMPS			"TimeStampS"
#define CP_PLYAER_STR_TIMESTAMPNS			"TimeStampNS"
#define CP_PLYAER_STR_VALUE					"Value"

///////////////////////////////字幕背景///////////////////////////////////////////
#define CP_PLYAER_STR_BACK_COLOR			"BackColor"
#define	CP_PLYAER_STR_BACKGROUND			"Background"
#define CP_APP_STR_BACKFPS					"BackFps"
#define	CP_PLYAER_STR_IS_SET				"IsSet"
#define CP_APP_STR_PICTURE					"Picture"

#define CP_APP_STR_ROWS						"Rows"
#define CP_APP_STR_COLUMNS					"Columns"
#define CP_APP_STR_CONTENTDIAPHANITY		"ContentDiaphanity"
#define CP_APP_STR_CONTENTSTYLE				"ContentStyle"
#define CP_APP_STR_CONTENTENCODE			"ContentEncode"
#define CP_APP_STR_BACKDIAPHANITY			"BackDiaphanity"
#define CP_APP_STR_CONTENTFONTSIZE			"ContentFontSize"
#define CP_APP_STR_CONTENTSPACE				"ContentSpace"
#define CP_APP_STR_RULERHEIGHT				"RulerHeight"
#define CP_APP_STR_RULERWIDTH				"RulerWidth"
#define CP_APP_STR_CONTENT					"Content"
#define CP_APP_STR_CONTENTFONT				"ContentFont"
#define CP_APP_STR_CONTENTCOLOR				"ContentColor"


#define	CP_APP_STR_MEDIA_BLOCK				"MediaBlock"


/////////////////////////////软件日志使用的字符串/////////////////////////////
#define CP_APP_STR_LOGS						"Logs"
#define	CP_APP_STR_LOG						"Log"
#define	CP_APP_STR_FILE_NAME				"FileName"
#define	CP_APP_STR_FILE_EXTENSION			"FileExtension"
#define	CP_APP_STR_FILE_PATH				"FilePath"
#define	CP_APP_STR_FILE_SIZE				"FileSize"
#define	CP_APP_STR_FILE_CREATE_TIME			"FileCreateTime"
#define	CP_APP_STR_FILE_MODIFY_TIME			"FileModifyTime"
#define	CP_APP_STR_FILE_DATA				"FileData"


//////////////////////////////////聚焦////////////////////////////////////////
#define CP_APP_STR_FOCUS					"Focus"
#define CP_APP_STR_FOCUS_TYPE				"FocusType"




///////////////////////////////////定义默认字符///////////////////////////////////////
#define CP_APP_STR_NULL_FLAG				"null"
#define CP_APP_STR_SPLIT_FLAG				'-'

#endif