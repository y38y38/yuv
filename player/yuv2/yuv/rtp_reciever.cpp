#include "stdafx.h"

#include "rtp_reciever.h"

RtpReciever::RtpReciever()
{
	return;
}


RtpReciever::~RtpReciever()
{
	return;
}
void RtpReciever::RecieveThread(void)
{
	CallbackPtr("test");
	return;
}
void RtpReciever::RegisterCallback(p_func func_ptr)
{
	CallbackPtr = func_ptr;
	return;
}


