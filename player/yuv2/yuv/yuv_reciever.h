#pragma once

#ifndef _YUV_RECIEVER_H_
#define _YUV_RECIEVER_H_

#include "stdint.h"

#include "yuv_setting.h"

class YuvReciever {
public:
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

private:
	uint8_t *RgbBuf;
	void SetRgbBufSize();
	void UpdateImage();
};


#endif //_YUV_RECIEVER_H_