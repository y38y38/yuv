#include "stdafx.h"

#include "stdlib.h"
#include <winsock.h>
#include "yuv_debug.h"
#include "stdio.h"

#include "test_rtp_sender.h"

TestRtpSender::TestRtpSender()
{

	HANDLE hThread;
	DWORD dwThreadId;

	//スレッド起動
	hThread = CreateThread(
		NULL, //セキュリティ属性
		0, //スタックサイズ
		(LPTHREAD_START_ROUTINE)SendThread, //スレッド関数
		NULL, //スレッド関数に渡す引数
		0, //作成オプション(0またはCREATE_SUSPENDED)
		&dwThreadId);//スレッドID	
	return;
}


TestRtpSender::~TestRtpSender()
{
	return;
}
struct RtpExtendHeader {
	uint16_t extended_sequnece_number;
	uint16_t srd_length;
	uint16_t f : 1;
	uint16_t srd_row_number : 15;
	uint16_t c : 1;
	uint16_t srd_offset : 15;
};
struct RtpHeader{
	uint8_t v : 2;
	uint8_t p : 1;
	uint8_t x : 1;
	uint8_t cc : 4;
	uint8_t m : 1;
	uint8_t pt : 7;
	uint16_t sequence_number;
	uint32_t time_stap;
	uint32_t ssrc;
};
void TestGetCrLine(char * frame, int line_number, char * line)
{
	for (int pixel = 0; pixel < 720 / 4; pixel++) {
		*(line + ((pixel * 4) + 5)) = *((frame + (720 * 480) + ((720 * 480) / 4) + (line_number * (720 / 2))) + pixel);
	}
	return;
}

void TestGetCbLine(char * frame, int line_number, char * line)
{
	for (int pixel = 0; pixel < 720 / 4; pixel++) {
		*(line + ((pixel * 4) + 4)) = *((frame + (720 * 480) + (line_number * (720 / 2))) + pixel);
	}
	return;
}


void TestGetYLine(char * frame, int line_number, char * line)
{
	for (int pixel = 0; pixel < 720; pixel++) {
		*(line + pixel) = *((frame + (line_number * 720)) + pixel);
	}
	return;
}

void TestSetRtpHeader(RtpHeader * rtp_header, int line_number)
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
	rtp_extend_header->srd_offset = 0;

	rtp_sequnec_number++;
	return;
}
void TestFrameSender(SOCKET sock, struct sockaddr_in addr, char* frame)
{
	int line_size = 720 + (720 / 2);
	int rtp_header_size = sizeof (struct RtpHeader) + sizeof(struct RtpExtendHeader);
	char *line_buf = (char*)malloc(line_size+ rtp_header_size);
	for (int line_number = 0; line_number < 720; line_number) {
		TestGetYLine(frame, line_number, line_buf + rtp_header_size);
		TestGetCbLine(frame, line_number, line_buf + rtp_header_size);
		TestGetCrLine(frame, line_number, line_buf + rtp_header_size);
		TestSetRtpHeader((struct RtpHeader*)line_buf, line_number);
		sendto(sock, line_buf, line_size + rtp_header_size, 0, (struct sockaddr *)&addr, sizeof(addr));
	}

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
	fopen_s(&in, "test.yuv", "r");

	if (in == NULL) {
		Win32Printf("error fopen_s\n");
		return;
	}

	int framesize = (720 * 480) + ((720 * 480) / 2);
	char * buf = (char*)malloc(framesize);
	while (!feof(in)) {
		size_t size;
		size = fread(&buf, 1, framesize, in);
		if (size != framesize) {
			Win32Printf("error fread %d\n", size);
			return;
		}
		TestFrameSender(sock, addr, buf);
	}
	free(buf);
	closesocket(sock);

	return;
}

DWORD WINAPI TestRtpSender::SendThread(LPVOID arg)
{
	WSAData wsaData;


	WSAStartup(MAKEWORD(2, 0), &wsaData);
	TestFileRtpSender();

	WSACleanup();

	return 0;
}



