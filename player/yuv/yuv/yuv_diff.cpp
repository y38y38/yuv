#include "stdafx.h"

#include "stdlib.h"

#include "yuv_debug.h"

#include "yuv_setting.h"

#include "rawvideo420.h"
#include "yuv4.h"

#include "yuv_diff.h"

YuvDiff::YuvDiff(void)
{
	YuvBuffer = NULL;
	Width = 0;
	Height = 0;
	return;
}

YuvDiff::~YuvDiff(void)
{
	return;
}

void YuvDiff::CreateDiff(uint8_t *img1, uint8_t *img2)
{
	uint8_t diff;
	for (uint32_t i = 0; i < Width; i++) {
		for (uint32_t j = 0; j < Height; j++) {
			short y1, y2, pb, pr;
			RawVideo420::getYPixel(img1, (i % Width) + (j * Width), &y1, &pb, &pr);
			RawVideo420::getYPixel(img2, (i % Width) + (j * Width), &y2, &pb, &pr);
			if (y1 > y2) {
				diff = y1 - y2;
			}
			else {
				diff = y2 - y1;
			}
			RawVideo420::setYPixel(diff, (i % Width) + (j * Width), YuvBuffer);
		}
	}

	return;
}
void YuvDiff::GetRgb(uint8_t *rgbbuf)
{
	RawVideo420::getRgb(YuvBuffer, Width, Height, rgbbuf, TRUE, TRUE, TRUE);
	return;
}

void YuvDiff::SetDiffTimes(int times)
{
	Times = times;
	return;
}
void YuvDiff::SetSize(uint32_t width, uint32_t height)
{
	Width = width;
	Height = height;

	if (YuvBuffer != NULL) {
		free(YuvBuffer);
	}

	YuvBuffer = (uint8_t *)malloc(Width * Height + ((Width * height) / 2));
	if (YuvBuffer == NULL) {
		Win32Printf("%hs %d malloc error", __func__, __LINE__);
	}

	return;
}


