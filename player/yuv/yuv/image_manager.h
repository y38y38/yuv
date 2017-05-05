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
	void Update(int frame_number, uint32_t width, uint32_t height, uint8_t *rgb_buf);

private:
	filebuffer g_filebuffer;
	void GetRgb(unsigned char *yuvbuffer, uint32_t width, uint32_t heigth, uint8_t *rgb_buf);
	int getFrameBufferSize(uint32_t widht, uint32_t height);


};


#endif // _IMAGE_MANAGER_H_
 