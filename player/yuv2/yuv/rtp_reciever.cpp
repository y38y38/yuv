#include "stdafx.h"

#include <winsock.h>

#include "yuv_debug.h"

#include "yuv_reciever.h"

#include "rtp_reciever.h"



//YuvReciever *RtpReciever::Parent;

//RtpReciever::RtpReciever(YuvReciever *parent)
RtpReciever::RtpReciever(void)
{
//	CallbackPtr = NULL;

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


RtpReciever::~RtpReciever()
{
	return;
}
DWORD WINAPI RtpReciever::RecieveThread(LPVOID arg)
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
		//Parent->RecievePacket("test");
	}


	closesocket(sock);

	WSACleanup();
#endif
	return 0;
}
#if 0
void RtpReciever::RegisterCallback(p_func func_ptr)
{
	CallbackPtr = func_ptr;
	return;
}
#endif


