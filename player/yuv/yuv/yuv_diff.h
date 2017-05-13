#pragma once

#ifndef _YUV_DIFF_
#define _YUV_DIFF_

#include "stdint.h"

class YuvDiff {
public:
	YuvDiff();
	~YuvDiff();

	void CreateDiff(uint8_t *img1, uint8_t *img2);
	void GetRgb(uint8_t *rgbbuf);

	void SetDiffTimes(int times);
	void SetSize(uint32_t width, uint32_t height);

private:
	int Times;
	uint32_t Width;
	uint32_t Height;
	uint8_t *YuvBuffer;
};

#endif // _YUV_DIFF_
