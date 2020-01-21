
//#include <stdlib.h>
//#include <string.h>

#if defined WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
//SDL
#include "SDL.h"
#include "SDL_thread.h"



//#define _WAVE_
#undef main



#define		BUF_SIZE				4096*500
FILE*		file;
int			read_len = 0;


//ȫ�ֱ���---------------------
static		Uint8					*audio_chunk;
static		Uint32					audio_len;
static		Uint8					*audio_pos;
//-----------------



/*  The audio function callback takes the following parameters:
stream: A pointer to the audio buffer to be filled
len: The length (in bytes) of the audio buffer (���ǹ̶���4096��)
�ص�����
ע�⣺mp3Ϊʲô���Ų�˳����
len=4096;audio_len=4608;�������512��Ϊ����512�������ٵ���һ�λص�����������
m4a,aac�Ͳ����ڴ�����(����4096)��
*/
void  fill_audio(void *udata, Uint8 *stream, int len){
	/*  Only  play  if  we  have  data  left  */
	SDL_memset(stream, 0, len);
	if (audio_len == 0)
		return;
	/*  Mix  as  much  data  as  possible  */
	len = (len > audio_len ? audio_len : len);
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	audio_pos += len;
	audio_len -= len;
}
//-----------------

int read_packet(void *opaque, uint8_t *buf, int buf_size)
{
	int					n = 0;
	int					tmp_read_len = 836;



	if (!feof(file)){
		//n = fread(buf, 1, buf_size, file);
		n = fread(buf, 1, tmp_read_len, file);
		read_len += n;

// #if defined WIN32
// 		Sleep(100);
// #else
// 		usleep(100000);
// #endif

		return n;
	}
	else
		return -1;
}


int decode_audio(char* no_use)
{
	AVFormatContext					*pFormatCtx = NULL;
	int								i = 0;
	int								audioStream = 0;
	int								ret_int = 0;
	int								samples = 0;
	AVCodecContext					*pCodecCtx = NULL;
	AVCodec							*pCodec = NULL;
	AVIOContext						*pb = NULL;
	AVInputFormat					*piFmt = NULL;
	AVInputFormat					*pFmt = NULL;
	char							url[1024] = { 0 };
	char							error_text[1024] = { 0, };
	uint8_t							*buf = NULL;



	strcpy(url, no_use);

	av_register_all();
	//avcodec_register_all();

	//֧������������
	avformat_network_init();

	file = fopen(url, "rb+");
	if (file == NULL)
		return -1;

	for (i = 0; i < 1; i++) {
		fread(error_text, 1, sizeof(error_text), file);
	}

	//
	buf = (uint8_t*)av_mallocz(sizeof(uint8_t)* BUF_SIZE);
	pb = avio_alloc_context(buf, BUF_SIZE, 0, NULL, read_packet, NULL, NULL);

	//̽����ڴ��л�ȡ����ý�����ĸ�ʽ
	if (av_probe_input_buffer(pb, &piFmt, "", NULL, 0, 0) < 0) {
		fprintf(stderr, "probe format failed\n");
		return -1;
	}
	else{
		fprintf(stdout, "format:%s[%s]\n", piFmt->name, piFmt->long_name);
	}

	//��ʼ��
	pFormatCtx = avformat_alloc_context();
	pFormatCtx->pb = pb;

	//��
	ret_int = avformat_open_input(&pFormatCtx, "", piFmt, NULL);
	if (ret_int != 0){
		printf("Couldn't open input stream.\n");
		av_strerror(ret_int, error_text, sizeof(error_text));
		return -1;
	}
	// Retrieve stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		printf("Couldn't find stream information.\n");
		return -1;
	}
	// Dump valid information onto standard error
	av_dump_format(pFormatCtx, 0, url, 0);

	// Find the first audio stream
	audioStream = -1;
	for (i = 0; i < pFormatCtx->nb_streams; i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
			break;
		}
	}

	if (audioStream == -1)
	{
		printf("Didn't find a audio stream.\n");
		return -1;
	}

	// Get a pointer to the codec context for the audio stream
	pCodecCtx = pFormatCtx->streams[audioStream]->codec;

	// Find the decoder for the audio stream
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		printf("Codec not found.\n");
		return -1;
	}

	// Open codec
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		printf("Could not open codec.\n");
		return -1;
	}

// 	av_free(pFormatCtx);
// 	av_free(pb);
// 	av_free(buf);

	FILE *pFile;
#ifdef _WAVE_
	pFile = fopen("output.wav", "wb");
	fseek(pFile, 44, SEEK_SET); //Ԥ���ļ�ͷ��λ��
#else
	pFile = fopen("output.pcm", "wb");
#endif

	AVPacket *packet = (AVPacket *)malloc(sizeof(AVPacket));
	AVFrame		decoded_frame;
	av_init_packet(packet);

	AVFrame	*pFrame;
	pFrame = av_frame_alloc();
	//pFrame = avcodec_alloc_frame();
	//�����Ƶ���ݴ�С��һ��С������ڴ档
	int out_linesize;
	//����ڴ��С
	//int out_buffer_size = av_samples_get_buffer_size(&out_linesize, pCodecCtx->channels, pCodecCtx->frame_size, pCodecCtx->sample_fmt, 1);
	//---------SDL--------------------------------------
	//��ʼ��
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		exit(1);
	}

	//�ṹ�壬����PCM���ݵ������Ϣ
	SDL_AudioSpec wanted_spec;
	wanted_spec.freq = pCodecCtx->sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = pCodecCtx->channels;
	wanted_spec.silence = 0;
	wanted_spec.samples = 1024; //����AAC��M4a���������Ĵ�С
	//wanted_spec.samples = 1152; //����MP3��WMAʱ����
	wanted_spec.callback = fill_audio;
	wanted_spec.userdata = pCodecCtx;

	//-----------------------------------------------------
	printf("Bitrate:\t %3d\n", pFormatCtx->bit_rate);
	printf("Decoder Name:\t %s\n", pCodecCtx->codec->long_name);
	printf("Channels:\t %d\n", pCodecCtx->channels);
	printf("Sample per Second\t %d \n", pCodecCtx->sample_rate);

	uint32_t ret, len = 0;
	int got_picture;
	int index = 0;
	struct SwrContext *au_convert_ctx;
	au_convert_ctx = swr_alloc();
	au_convert_ctx = swr_alloc_set_opts(au_convert_ctx, AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_S16, 44100,
		pCodecCtx->channel_layout, (enum AVSampleFormat)pCodecCtx->sample_fmt, pCodecCtx->sample_rate, 0, NULL);
	swr_init(au_convert_ctx);

	int out_buffer_size = 0;
	uint8_t *out_buffer = 0;
	uint8_t *extended_out_buffer = 0;

	while (av_read_frame(pFormatCtx, packet) >= 0)
	{
		if (packet->stream_index == audioStream)
		{
			ret = avcodec_send_packet(pCodecCtx, packet);
			if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
				printf("Error in decoding audio frame.\n");
				exit(0);
				return -1;
			}
			ret = avcodec_receive_frame(pCodecCtx, pFrame);
			if (ret < 0 && ret != AVERROR_EOF) {
				ret_int = -1;
				return -1;
			}

			if (!samples) {
				samples = av_rescale_rnd(
					swr_get_delay(au_convert_ctx, pFrame->sample_rate) + pFrame->nb_samples,
					44100, 44100, AV_ROUND_INF);
				out_buffer_size = av_samples_get_buffer_size(&out_linesize, 2, samples, AV_SAMPLE_FMT_S16, 1);
				out_buffer = malloc(out_buffer_size);
				extended_out_buffer = malloc(out_buffer_size);
				wanted_spec.samples = samples;
				if (SDL_OpenAudio(&wanted_spec, NULL) < 0)//���裨2������Ƶ�豸 
				{
					printf("can't open audio.\n");
					return 0;
				}
			}

			//�����AV_SAMPLE_FMT_FLTP��ʽ����Ҫ���д�����������
			//���ִ����Ǻܺã�������һ������
			if (AV_SAMPLE_FMT_FLTP == pFrame->format) {
				int nb_samples = pFrame->nb_samples;
				int channels = pFrame->channels;
				int outputBufferLen = nb_samples & channels * 2;
				int16_t* outputBuffer = (int16_t*)out_buffer;

				for (int i = 0; i < nb_samples; i++)
				{
					for (int c = 0; c < channels; c++)
					{
						float* extended_data = (float*)pFrame->extended_data[c];
						float sample = extended_data[i];
						if (sample < -1.0f) sample = -1.0f;
						else if (sample > 1.0f) sample = 1.0f;
						outputBuffer[i * channels + c] = (int16_t)round(sample * 32767.0f);
						//outputBuffer[i * channels + c] = (int16_t)round(sample * 3.40282e+038);
					}
				}
			}

			ret = swr_convert(au_convert_ctx, &out_buffer, out_linesize, (const uint8_t **)pFrame->data, pFrame->nb_samples);
			if (ret < 0)
			{
				printf("Error in decoding audio frame.\n");
				exit(0);
			}

			printf("index:%5d\t pts %5d\n", index, packet->pts);
			//ֱ��д��
#if 0
			fwrite(out_buffer, 1, out_linesize, pFile);
#endif
			index++;
			//}
#if 1
			//---------------------------------------
			//printf("begin....\n"); 
			//������Ƶ���ݻ���,PCM����
			audio_chunk = (Uint8 *)out_buffer;
			//������Ƶ���ݳ���
			audio_len = out_linesize;
			//audio_len = 4096;
			//����mp3��ʱ���Ϊaudio_len = 4096
			//���Ƚ���������������������MP3һ֡����4608
			//ʹ��һ�λص�������4096�ֽڻ��壩���Ų��꣬���Ի�Ҫʹ��һ�λص����������²��Ż���������
			//���ó�ʼ����λ��
			audio_pos = audio_chunk;
			//�ط���Ƶ���� 
			SDL_PauseAudio(0);
			//printf("don't close, audio playing...\n"); 
			while (audio_len > 0)//�ȴ�ֱ����Ƶ���ݲ������! 
				SDL_Delay(1);
			//---------------------------------------
#endif
		}
		//av_free_packet(packet);
	}

#ifdef _WAVE_
	fseek(pFile, 0, SEEK_SET);
	struct WAVE_HEADER wh;

	memcpy(wh.header.RiffID, "RIFF", 4);
	wh.header.RiffSize = 36 + len;
	memcpy(wh.header.RiffFormat, "WAVE", 4);

	memcpy(wh.format.FmtID, "fmt ", 4);
	wh.format.FmtSize = 16;
	wh.format.wavFormat.FormatTag = 1;
	wh.format.wavFormat.Channels = pCodecCtx->channels;
	wh.format.wavFormat.SamplesRate = pCodecCtx->sample_rate;
	wh.format.wavFormat.BitsPerSample = 16;
	calformat(wh.format.wavFormat); //Calculate AvgBytesRate and BlockAlign

	memcpy(wh.data.DataID, "data", 4);
	wh.data.DataSize = len;

	fwrite(&wh, 1, sizeof(wh), pFile);
#endif
	SDL_CloseAudio();//�ر���Ƶ�豸 
	// Close file
	fclose(pFile);
	// Close the codec
	avcodec_close(pCodecCtx);
	// Close the video file
	//av_close_input_file(pFormatCtx);

	return 0;
}


int main(int argc, char** argv)
{
	//char filename[]="E:\\project_work\\project\\css_media_server\\parking_console\\data\\30608_NewOrange_Stream0_1_audio_media_data.txt";
	char filename[] = "E:\\project_work\\project\\video\\ffmpeg-20150601-git-d8bbb99-win32-static\\ffmpeg-20150601-git-d8bbb99-win32-static\\bin\\2_VideoSourceToken1_audio_media_data.txt";
	//char filename[]="rtsp://192.168.1.168:554/0";
	//char filename[] = "E:\\project_work\\project\\css_player_fix_org\\platform\\win32\\css_player\\cp_player\\ffmpeg_codec_module_probe_media.data";
	//char filename[] = "C:\\Users\\fz\\Downloads\\simplest_ffmpeg_audio_player_change\\simplest_ffmpeg_audio_player\\meilikaiguo.mp3";
	if (decode_audio(filename) == 0)
		printf("Decode audio successfully.\\n");

	return 0;
}

