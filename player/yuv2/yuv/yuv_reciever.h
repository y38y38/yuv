#pragma once

#ifndef _YUV_RECIEVER_H_
#define _YUV_RECIEVER_H_

#include "stdint.h"

#include "yuv_setting.h"

//#include "rtp_reciever.h"

class YuvReciever {
public:
	static YuvReciever& GetInst(void) {
		static YuvReciever singleton;
		return singleton;
	}
	YuvReciever();
	~YuvReciever();
	void SetPixel(YuvSetting::YuvSize size);
	uint32_t GetWidthSize(void);
	uint32_t GetHeightSize(void);
	void SetFormat(YuvSetting::YuvFormat format);
	YuvSetting::YuvFormat GetFormat(void);
	uint8_t *GetRgbBuf(void);
	void Init(void);
	void SetView(YuvSetting::YuvView view);
	YuvSetting::YuvView GetView(void);
	void RecievePacket(char *buf, int size);
	void SetRgb(void);

private:
	uint8_t *RgbBuf;
	uint8_t *YuvBuf;
	void SetRgbBufSize();
	void UpdateImage();
	static DWORD WINAPI RecieveThread(LPVOID arg);
	void GetRtpHeader(char* buf);
	//int *reciever;
//	RtpReciever *reciever;
	uint8_t st2110GetY(uint8_t* buf, int pixel, int max_width, int max_height);
	uint8_t st2110GetCb(uint8_t* buf, int pixel, int max_width, int max_height);
	uint8_t st2110GetCr(uint8_t* buf, int pixel, int max_width, int max_height);

};


#endif //_YUV_RECIEVER_H_