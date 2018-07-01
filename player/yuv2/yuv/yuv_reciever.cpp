#include "stdafx.h"

#include "stdlib.h"

#include "yuv_debug.h"

#include <winsock.h>

#include "window_manager.h"
#include "rtp_reciever.h"

#include "yuv_reciever.h"

#include "test_rtp_sender.h"


#include "rtp_header.h"

#include "yuvrgb.h"

YuvReciever::YuvReciever(void)
{
	RgbBuf= NULL;
    YuvBuf = NULL;
	//	reciever = new RtpReciever(this);
	return;
}

YuvReciever::~YuvReciever(void)
{
	return;
}
void YuvReciever::SetRgbBufSize(void)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	if (RgbBuf != NULL) {
		free(RgbBuf);
	}
	RgbBuf = (uint8_t*)malloc(width * height * 3);
	if (RgbBuf == NULL) {
		Win32Printf("%hs %d malloc error", __FUNCTION__, __LINE__);
		//エラー処理
	}
	if (YuvBuf != NULL) {
		free(YuvBuf);
	}
	YuvBuf = (uint8_t*)malloc((width * height ) + ((width * height)/2));
	if (YuvBuf == NULL) {
		Win32Printf("%hs %d malloc error", __FUNCTION__, __LINE__);
		//エラー処理
	}
	memset(YuvBuf, 0x80, (720 * 480) + ((720 * 480) / 2));

	return;
}

void YuvReciever::UpdateImage(void)
{
	Win32Printf("%hs %d", __FUNCTION__, __LINE__);
	WindowManager::GetInst().Update();
	return;
}


void YuvReciever::SetPixel(YuvSetting::YuvSize size)
{
	YuvSetting::GetInst().SetSize(size);


	//画像サイズが変更されたらバッファサイズを変更する必要がある。
	SetRgbBufSize();

	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	//画像サイズが変更されたら画像の更新も行う。
	UpdateImage();
	return;
}

uint32_t YuvReciever::GetWidthSize(void)
{
	if (YuvSetting::GetInst().GetView() == YuvSetting::YUV_VIEW_SINGLE) {
		return 	YuvSetting::GetInst().GetWidthSize();
	}
	else {
		return 	(YuvSetting::GetInst().GetWidthSize() * 2);
	}

}
uint32_t YuvReciever::GetHeightSize(void)
{
	return	YuvSetting::GetInst().GetHeightSize();
}
void YuvReciever::SetFormat(YuvSetting::YuvFormat format)
{
	YuvSetting::GetInst().SetFormat(format);

	WindowManager::GetInst().Update();
	return;
}
YuvSetting::YuvFormat YuvReciever::GetFormat(void)
{
	return YuvSetting::GetInst().GetFormat();
}


uint8_t *YuvReciever::GetRgbBuf(void)
{
	return RgbBuf;
}
void YuvReciever::Init(void)
{
	YuvSetting::GetInst().InitSetting();
	SetRgbBufSize();

	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = (int)YuvSetting::GetInst().GetHeightSize();

	HANDLE hThread;
	DWORD dwThreadId;

	//	Parent = parent;


	//スレッド起動
	hThread = CreateThread(
		NULL, //セキュリティ属性
		0, //スタックサイズ
		(LPTHREAD_START_ROUTINE)RecieveThread, //スレッド関数
		NULL, //スレッド関数に渡す引数
		0, //作成オプション(0またはCREATE_SUSPENDED)
		&dwThreadId);//スレッドID	

	return;
}
void YuvReciever::SetView(YuvSetting::YuvView view)
{
	YuvSetting::GetInst().SetView(view);
	WindowManager::GetInst().Update();
	return;
}

YuvSetting::YuvView YuvReciever::GetView(void)
{
	return YuvSetting::GetInst().GetView();
}


void YuvReciever::GetRtpHeader(char* buf)
{
struct RtpHeader *rtp_header = (struct RtpHeader *)buf;
Win32Printf("rtpheader:sequnece_number = %d\n", rtp_header->sequence_number);
struct RtpExtendHeader * rtp_ext_header = (struct RtpExtendHeader *)(buf + sizeof(struct RtpHeader));

Win32Printf("rtp_ext_header:srd_length = %d\n", rtp_ext_header->srd_length);
Win32Printf("rtp_ext_header:srd_row_number = %d\n", rtp_ext_header->srd_row_number);
Win32Printf("rtp_ext_header:srd_offset = %d\n", rtp_ext_header->srd_offset);

return;
}
uint8_t YuvReciever::st2110GetY(uint8_t* buf, int pixel, int max_width, int max_height)
{
	uint8_t y;

	int line;
	if (pixel == 0) {
		line = 0;
	}
	else {
		line = pixel / max_width;
	}

	int line_double;
	if (pixel == 0) {
		line_double = 0;
	}
	else {
		line_double = pixel / (max_width * 2);
	}

	int byte_per_line_doulbe = (max_width * 2) + (max_width);

	//1st line
	if ((line % 2) == 0) {
		if ((pixel % 2) == 0) {
			y = *(buf + (line_double * byte_per_line_doulbe) + (((pixel % max_width) / 2) * 6));
		}
		else {
			y = *(buf + (line_double * byte_per_line_doulbe) + (((pixel % max_width) / 2) * 6) + 1);
		}
	}
	else {
		if ((pixel % 2) == 0) {
			y = *(buf + (line_double * byte_per_line_doulbe) + (((pixel % max_width) / 2) * 6) + 2);
		}
		else {
			y = *(buf + (line_double * byte_per_line_doulbe) + (((pixel % max_width) / 2) * 6) + 3);
		}
	}
	return y;
}
uint8_t YuvReciever::st2110GetCb(uint8_t* buf, int pixel, int max_width, int max_height)
{
	uint8_t cb;
	cb = *(buf + (pixel * 6) + 4);
	return cb;
}
uint8_t YuvReciever::st2110GetCr(uint8_t* buf, int pixel, int max_width, int max_height)
{
	uint8_t cr;
	cr = *(buf + (pixel * 6) + 5);
	return cr;
}


void YuvReciever::SetRgb(void)
{
	int pixel = 0;
	uint8_t y, cb, cr;
#if 0
	for (int i = 0; i < ((720 * 480) + ((720 * 480) / 2)); i++) {
		if ((i % 6) == 0) {
			*(YuvBuf + i) = 0x00;

		}
		else if ((i % 6) == 1) {
			*(YuvBuf + i) = 0x00;
		}
		else if ((i % 6) == 2) {
			*(YuvBuf + i) = 0x80;
		}
		else if ((i % 6) == 3) {
			*(YuvBuf + i) = 0x80;
		}
		else if ((i % 6) == 4) {
			*(YuvBuf + i) = 0x80;
		}
		else if ((i % 6) == 5) {
			*(YuvBuf + i) = 0x80;
		}
	}
#endif
	//	memset(YuvBuf, 0x80, (720 * 480) + ((720 * 480) / 2));

	for (int height = 0; height < 480; height++) {
		for (int width = 0; width < 720; width++) {
			int pixel = (height * 720) + width;
			if (pixel == 1440) {
//				Win32Printf("byte_offset:\n");
			}
			y = st2110GetY(YuvBuf, pixel, 720, 480);
#if 0
			if ((width < 10)) {
				y = 0x00;
			}
			if ((width > 710)) {
				y = 0x00;
			}
#endif
			if ((height != 0) && (height != 1)) {
				//y = 0x80;
			}
			int cb_height = 0;
			if (height == 0) {
				cb_height = 0;
			}
			else {
				cb_height = height / 2;
			}
			int cb_width = 0;
			if (width == 0) {
				cb_width = 0;
			}
			else {
				cb_width = width / 2;
			}

			int cb_pixel = (cb_height * 360) + cb_width;
			cb = st2110GetCb(YuvBuf, cb_pixel, 360, 240);
			cr = st2110GetCr(YuvBuf, cb_pixel, 360, 240);
			if (height == 0) {
				Win32Printf("%d %d\n", cb_pixel, cb);
			}
			//	y = 0x80;
//			cb = 0x80;
//			cr = 0x80;
			YuvRgb::ypbpr2rgb(y, cb, cr, RgbBuf + (pixel * 3));
		}
	}

	return;
}

void YuvReciever::RecievePacket(char *buf, int size)
{
//	GetRtpHeader(buf);
	struct RtpHeader *rtp_header = (struct RtpHeader *)buf;
	struct RtpExtendHeader * rtp_ext_header = (struct RtpExtendHeader *)(buf + sizeof(struct RtpHeader));

	int srd_length = rtp_ext_header->srd_length;
	int srd_row_number = rtp_ext_header->srd_row_number;
	int srd_offset = rtp_ext_header->srd_offset;
	uint32_t width = YuvSetting::GetInst().GetWidthSize();

	uint32_t byte_offset = (srd_row_number * ((width + (width / 2)))) + ((srd_offset * 2) + (srd_offset));

	static uint32_t prev_byte_offset = 0;
	if (prev_byte_offset > byte_offset) {
		//次のビデオフレームが到着した。そのため前のビデオが完了したので、表示する。
		SetRgb();
		memset(YuvBuf, 0x80, (720 * 480) + ((720 * 480) / 2));
		WindowManager::GetInst().Update();
	}
//	if (srd_row_number ==0 ){
		memcpy(YuvBuf + byte_offset, rtp_ext_header + 1, srd_length);
//		Win32Printf("byte_offset:%d srd_length %d\n", byte_offset, srd_length);
//	}
	//else {
	//	memset(YuvBuf + byte_offset, 0x80,  srd_length);

	//}
#if 0
	Win32Printf("recv:%d %d %d %d %d\n", width,
		                            srd_row_number, 
		                            srd_offset,
		                            (srd_row_number * ((width + (width /2)))) + ((srd_offset * 2) + ( srd_offset)),
		                            srd_length);
#endif
	//memcpy(YuvBuf , rtp_ext_header + 1, srd_length);

	if (byte_offset + srd_length == ((720 * 480) + (720 * 480 / 2))) {
		//全ビデオフレームがそろった表示する。
		SetRgb();
		memset(YuvBuf, 0x80, (720 * 480) + ((720*480) /2 ));

		WindowManager::GetInst().Update();

		//次のビデオフレームが来ても表示しないように。prev_byte_offsetを更新する。
		prev_byte_offset = 0;

	}
	else {
		prev_byte_offset = byte_offset;
	}
	//次回のチェックのためにprev_byte_offsetを更新する。

}

DWORD WINAPI YuvReciever::RecieveThread(LPVOID arg)
{
#if 1
	WSAData wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	char buf[2048];
	Win32Printf("%hs %d ", __FUNCTION__, __LINE__);

	WSAStartup(MAKEWORD(2, 0), &wsaData);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);//port num
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(sock, (struct sockaddr *)&addr, sizeof(addr));

	TestRtpSender::TestRtpSender();

	for (;;) {
		memset(buf, 0, sizeof(buf));
		size_t recvsize = recv(sock, buf, sizeof(buf), 0);
		YuvReciever::GetInst().RecievePacket(buf, (int)recvsize);
	}

	closesocket(sock);

	WSACleanup();
#endif
	return 0;
}
