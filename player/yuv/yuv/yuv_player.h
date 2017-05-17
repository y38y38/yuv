#pragma once

#ifndef _YUV_PLAYER_H_
#define _YUV_PLAYER_H_

#include "stdint.h"

#include "yuv_setting.h"
#include "yuv_diff.h"

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
	void SetDiffMode(YuvSetting::YuvDiffMode diff);
	YuvSetting::YuvDiffMode GetDiffMode(void);
	void SetDiffTimes(YuvSetting::YuvDiffTimes times);

	typedef enum {
		YUV_WINDOW_LEFT_TOP = 0,
		YUV_WINDOW_LEFT_BOTTOM = 0,
		YUV_WINDOW_RIGHT_TOP = 1,
		YUV_WINDOW_RIGHT_BOTTOM = 1,
	} YUV_WINDOW_POS;

	void SetMouse(YUV_WINDOW_POS pos);
	void ReleaseMouse(void);

private:
	const static int MAX_FILE_NUM = 4;
	uint32_t FileNum;
	ImageManager Img[MAX_FILE_NUM];
	YuvDiff Diff;

	uint8_t *RgbBuf[MAX_FILE_NUM];
	uint8_t *MultiRgbBuf;
	int SingleViewIndex;
	bool OnMouse;
	YUV_WINDOW_POS DiffPosition;

	void SetRgbBufSize(void);
	void UpdateImageAll(int  frame_number);
	void UpdateImage(int image_index, int  frame_number);
	void UpdateRgbBuf();
	int GetFileNum(void);
	bool IsImageDiff(void);

};


#endif //_YUV_PLAYER_H_