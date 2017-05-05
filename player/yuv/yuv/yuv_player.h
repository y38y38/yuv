#pragma once

#ifndef _YUV_PLAYER_H_
#define _YUV_PLAYER_H_

#include "stdint.h"

#include "yuv_setting.h"

#include "image_manager.h"

class YuvPlayer {
public:
	YuvPlayer();
	~YuvPlayer();
	void SetPixel(YuvSetting::YuvSize size);
	uint32_t GetWidthSize(void);
	uint32_t GetHeightSize(void);
	void InputFile(TCHAR *filename);
	uint8_t *GetRgbBuf(void);
	void Init(void);
	void NextFrame(void);
	void PrevFrame(void);

private:
	ImageManager Img;
	uint8_t *rgb_buf;

};


#endif //_YUV_PLAYER_H_