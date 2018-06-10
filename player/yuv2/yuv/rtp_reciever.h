#pragma once

#ifndef _RTP_RECIEVER_H_
#define _RTP_RECIEVER_H_

#include "stdint.h"

#include "yuv_reciever.h"

class RtpReciever {
public:
//	typedef void(*p_func)(char*);

//	RtpReciever(YuvReciever *parent);
	RtpReciever();
	~RtpReciever();

//	void RegisterCallback(p_func func_ptr);

	static DWORD WINAPI RecieveThread(LPVOID arg);
//	static p_func CallbackPtr;
private:
//	static YuvReciever * Parent;
};


#endif //_RTP_RECIEVER_H_
