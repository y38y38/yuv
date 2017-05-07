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
	void NextImage(void);
	void PrevImage(void);
	void SetView(YuvSetting::YuvView view);
	YuvSetting::YuvView GetView(void);

private:
	const static int MAX_FILE_NUM = 4;
	uint32_t FileNum;
	ImageManager Img[MAX_FILE_NUM];
	uint8_t *RgbBuf[MAX_FILE_NUM];
	int SingleViewIndex;

	void UpdateRgbBuf(void);
	void UpdateImage(int image_index, int  frame_number);

};


#endif //_YUV_PLAYER_H_