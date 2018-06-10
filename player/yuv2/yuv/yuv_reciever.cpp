#include "stdafx.h"

#include "stdlib.h"

#include "yuv_debug.h"

#include <winsock.h>

#include "window_manager.h"
#include "rtp_reciever.h"

#include "yuv_reciever.h"


YuvReciever::YuvReciever(void)
{
	RgbBuf[1] = NULL;
//	reciever = new RtpReciever(this);
	HANDLE hThread;
	DWORD dwThreadId;

	//	Parent = parent;

	//�X���b�h�N��
	hThread = CreateThread(
		NULL, //�Z�L�����e�B����
		0, //�X�^�b�N�T�C�Y
		(LPTHREAD_START_ROUTINE)RecieveThread, //�X���b�h�֐�
		NULL, //�X���b�h�֐��ɓn������
		0, //�쐬�I�v�V����(0�܂���CREATE_SUSPENDED)
		&dwThreadId);//�X���b�hID	
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
		//�G���[����
	}

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


	//�摜�T�C�Y���ύX���ꂽ��o�b�t�@�T�C�Y��ύX����K�v������B
	SetRgbBufSize();

	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	//�摜�T�C�Y���ύX���ꂽ��摜�̍X�V���s���B
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
void YuvReciever::RecievePacket(char *buf)
{

}

DWORD WINAPI YuvReciever::RecieveThread(LPVOID arg)
{
#if 1
	WSAData wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	char buf[2048];

	WSAStartup(MAKEWORD(2, 0), &wsaData);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);//port num
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(sock, (struct sockaddr *)&addr, sizeof(addr));

	for (;;) {
		memset(buf, 0, sizeof(buf));
		recv(sock, buf, sizeof(buf), 0);
		YuvReciever::GetInst().RecievePacket(buf);
	}

	closesocket(sock);

	WSACleanup();
#endif
	return 0;
}
