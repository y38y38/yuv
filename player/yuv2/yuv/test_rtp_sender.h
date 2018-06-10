#pragma once

#ifndef _TEST_RTP_SENDER_H_
#define _TEST_RTP_SENDER_H_

#include "stdint.h"

class TestRtpSender {
public:

	TestRtpSender();
	~TestRtpSender();

	static DWORD WINAPI SendThread(LPVOID arg);
private:
};


#endif //_RTP_RECIEVER_H_
