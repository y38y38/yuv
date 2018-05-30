#pragma once

#ifndef _RTP_RECIEVER_H_
#define _RTP_RECIEVER_H_

#include "stdint.h"

class RtpReciever {
public:
	typedef void(*p_func)(char*);

	RtpReciever();
	~RtpReciever();

	void RegisterCallback(p_func func_ptr);

private:
	void RecieveThread(void);
	p_func CallbackPtr;
};


#endif //_RTP_RECIEVER_H_
