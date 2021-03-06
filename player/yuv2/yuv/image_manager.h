#pragma once

#ifndef _IMAGE_MANAGER_H_
#define _IMAGE_MANAGER_H_

#include <tchar.h>
#include "stdint.h"

#include "filebuffer.h"

class ImageManager {
public:
	ImageManager();
	~ImageManager();
	void Init(TCHAR *filename);
	void SetSize(uint32_t width, uint32_t height);
	void UpdateYuv(int frame_number);
	void SetRgbBuf(uint8_t *rgb_buf);
	uint8_t *GetYuvBuf();
	void Update(int frame_number, uint8_t *rgb_buf);

	uint32_t GetFrameNumber(void);

	TCHAR *GetFileName(void);

	void SetSignalY(bool y);
	void SetSignalCb(bool cb);
	void SetSignalCr(bool cr);


private:
	filebuffer Buffer;
	uint32_t FrameNumber;
	uint8_t *YuvBuffer;
	uint32_t Width;
	uint32_t Height;

	void GetRgb(uint8_t *yuvbuffer, uint32_t width, uint32_t heigth, uint8_t *rgb_buf);
	int getFrameBufferSize(uint32_t widht, uint32_t height);

	bool SignalY;
	bool SignalCb;
	bool SignalCr;
	
};


#endif // _IMAGE_MANAGER_H_
 