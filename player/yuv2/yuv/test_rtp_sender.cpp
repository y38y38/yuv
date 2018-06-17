#include "stdafx.h"

#include "stdlib.h"
#include <winsock.h>
#include "yuv_debug.h"
#include "stdio.h"

#include "test_rtp_sender.h"

#include "rtp_header.h"

TestRtpSender::TestRtpSender()
{

	HANDLE hThread;
	DWORD dwThreadId;
	Win32Printf("%hs %d", __FUNCTION__, __LINE__);
#if 1
	//スレッド起動
	hThread = CreateThread(
		NULL, //セキュリティ属性
		0, //スタックサイズ
		(LPTHREAD_START_ROUTINE)SendThread, //スレッド関数
		NULL, //スレッド関数に渡す引数
		0, //作成オプション(0またはCREATE_SUSPENDED)
		&dwThreadId);//スレッドID	
#endif
	return;
}


TestRtpSender::~TestRtpSender()
{
	return;
}

char rawVideoGetY(char *frame, int pixel, int width, int height)
{
	return *(frame + pixel);
}

//y_height, y_width at y posision
char rawVideoGetCb(char *frame, int pixel, int y_width, int y_height)
{
	return *(frame + (y_width * y_height) + pixel);
}

//y_height, y_width  at y posision
char rawVideoGetCr(char *frame, int pixel, int y_width, int y_height)
{
	return *(frame + (y_width * y_height) + ((y_width * y_height) / 4) + pixel );
}

void st2110SetY(char *frame, int pixel, char y, int width , int height)
{
	int line;
	if (pixel == 0) {
		line = 0;
	}
	else {
		line = pixel / width;
	}

	int line_double;
	if (pixel == 0) {
		line_double = 0;
	}
	else {
		line_double = pixel / (width * 2);
	}

	int byte_per_line_doulbe = (width * 2 ) + (width / 2);

	//1st line
	if ((line % 2) == 0) {
		if ((pixel % 2) == 0) {
			*(frame + (line_double * byte_per_line_doulbe) + (pixel % width)) = y;
		}
		else {
			*(frame + (line_double * byte_per_line_doulbe) + (pixel % width) + 1) = y;
		}
	} else {
		if ((pixel % 2) == 0) {
			*(frame + (line_double * byte_per_line_doulbe) + (pixel % width) + 2) = y;
		}
		else {
			*(frame + (line_double * byte_per_line_doulbe) + (pixel % width) + 3) = y;
		}
	}
	return;
}

void st2110SetCb(char *frame, int pixel, char cb)
{
	*(frame + (pixel * 6) + 4) = cb;
	return;
}

void st2110SetCr(char *frame, int pixel, char cr)
{
	*(frame + (pixel * 6) + 4) = cr;
	return;
}

void TestSetRtpHeader(RtpHeader * rtp_header, int line_number, int start_h)
{
	static uint32_t rtp_sequnec_number = 0;
	rtp_header->v = 2;
	rtp_header->p = 0; //padding
	rtp_header->x = 1; //extension
	rtp_header->cc = 0;// miss
	rtp_header->m = 1;
	rtp_header->pt = 0; //t.b.d.  must refernece st2110-10
	rtp_header->sequence_number = (uint16_t)rtp_sequnec_number;
	rtp_header->ssrc = 0x0; //t.b.d must refernce rfc 3550

	RtpExtendHeader * rtp_extend_header = (RtpExtendHeader *)(rtp_header + 1);
	rtp_extend_header->extended_sequnece_number = (uint16_t)(rtp_sequnec_number >> 16);
	rtp_extend_header->srd_length = (uint16_t)((720 * 480) + ((720 * 480) / 2));
	rtp_extend_header->f = 0;
	rtp_extend_header->srd_row_number = line_number;
	rtp_extend_header->srd_offset = start_h;

	rtp_sequnec_number++;
	return;
}
void TestRawVideo2St2110Frame(char *frame, char *st2110)
{
	//get y
	for (int pixel = 0; pixel < 720 * 480; pixel++) {
		char y = rawVideoGetY(frame, pixel, 720, 480);
		st2110SetY(frame, pixel, y, 720, 480);
	}
	for (int pixel = 0; pixel < 360 * 240; pixel++) {
		char cb = rawVideoGetCb(frame, pixel, 720, 480);
		st2110SetCb(frame, pixel, cb);
		char cr = rawVideoGetCr(frame, pixel, 720, 480);
		st2110SetCr(frame, pixel, cr);
	}
}

void GetRtpHeader(char* buf)
{
	struct RtpHeader *rtp_header = (struct RtpHeader *)buf;
	Win32Printf("send rtpheader:sequnece_number = %d\n", rtp_header->sequence_number);
	struct RtpExtendHeader * rtp_ext_header = (struct RtpExtendHeader *)buf + sizeof(struct RtpHeader);

	Win32Printf("send rtp_ext_header:srd_length = %d\n", rtp_ext_header->srd_length);
	Win32Printf("send rtp_ext_header:srd_row_number = %d\n", rtp_ext_header->srd_row_number);
	Win32Printf("send rtp_ext_header:srd_offset = %d\n", rtp_ext_header->srd_offset);

	return;
}

void TestFrameSender(SOCKET sock, struct sockaddr_in addr, char* frame)
{
	char *st2110_buf = (char*)malloc((720 * 480) + ((720 * 480) / 2));
	if (st2110_buf == NULL) {
		return;
	}
	TestRawVideo2St2110Frame(frame, st2110_buf);

	int line_size = 720 + (720 / 2);//1回に送信するデータ数

	int rtp_header_size = sizeof (struct RtpHeader) + sizeof(struct RtpExtendHeader);
	char *line_buf = (char*)malloc(line_size+ rtp_header_size);
	if (line_buf == NULL) {
		return;
	}
#if 1
	for (int line_number = 0; line_number < 480; line_number += 2) {
		//TestSetRtpHeader((struct RtpHeader*)line_buf, line_number, 0);
		//memcpy(line_buf + rtp_header_size, st2110_buf + (line_number * line_size), line_size);
		//GetRtpHeader(line_buf);
		//sendto(sock, line_buf, line_size + rtp_header_size, 0, (struct sockaddr *)&addr, sizeof(addr));

		//TestSetRtpHeader((struct RtpHeader*)line_buf, line_number, ((720 * 480) + ((720 * 480) / 2)) / 2);
		//memcpy(line_buf + rtp_header_size, st2110_buf + ((line_number + 1) * line_size), line_size);
		//GetRtpHeader(line_buf);
		sendto(sock, line_buf, line_size + rtp_header_size, 0, (struct sockaddr *)&addr, sizeof(addr));
	}
#endif
	free(st2110_buf);

	return;
}

void TestFileRtpSender(void) {
	SOCKET sock;
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	FILE * in;
//	fopen_s(&in, "c:\\work\\y38y38\\test.yuv", "r");
	fopen_s(&in, "test.yuv", "rb");

	if (in == NULL) {
		Win32Printf("error fopen_s\n");
		return;
	}

	int framesize = (720 * 480) + ((720 * 480) / 2);
	char * buf = (char*)malloc(framesize);
	while (!feof(in)) {
		size_t size;
		size = fread(buf, 1, framesize, in);
		if (size != framesize) {
			Win32Printf("error fread %d\n", size);
			break;
		}
		TestFrameSender(sock, addr, buf);
	}
	free(buf);
	closesocket(sock);
	Win32Printf("end of file\n");

	return;
}

DWORD WINAPI TestRtpSender::SendThread(LPVOID arg)
{
	WSAData wsaData;

	Win32Printf("%hs %d", __FUNCTION__, __LINE__);

	WSAStartup(MAKEWORD(2, 0), &wsaData);
	TestFileRtpSender();

	WSACleanup();

	return 0;
}



