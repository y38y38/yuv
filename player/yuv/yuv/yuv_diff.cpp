#include "stdafx.h"

#include "stdlib.h"

#include "yuv_debug.h"

#include "yuv_setting.h"

#include "rawvideo420.h"
#include "yuv4.h"
#include "cmm.h"

#include "yuv_diff.h"

YuvDiff::YuvDiff(void)
{
	YuvBuffer = NULL;
	Width = 0;
	Height = 0;
	Times = 1;
	return;
}

YuvDiff::~YuvDiff(void)
{
	return;
}

void YuvDiff::CreateDiff(uint8_t *img1, uint8_t *img2)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	int8_t diff;
	for (uint32_t i = 0; i < Width; i++) {
		for (uint32_t j = 0; j < Height; j++) {
			short y1, y2, pb, pr;
			if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
				RawVideo420::getYPixel(img1, (i % Width) + (j * Width), &y1, &pb, &pr);
				RawVideo420::getYPixel(img2, (i % Width) + (j * Width), &y2, &pb, &pr);
			} else if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_CMM) {
				Cmm::getYPixel(img1, (i % Width) + (j * Width), &y1, &pb, &pr, width, height);
				Cmm::getYPixel(img2, (i % Width) + (j * Width), &y2, &pb, &pr, width, height);
			} else {
				Yuv4::getYPixel(img1, (i % Width) + (j * Width), &y1, &pb, &pr, width, height);
				Yuv4::getYPixel(img2, (i % Width) + (j * Width), &y2, &pb, &pr, width, height);

			}
			diff = 0x80 + ((y1 - y2)  * Times);
			if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
				RawVideo420::setYPixel(diff, (i % Width) + (j * Width), YuvBuffer);
			} else if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_CMM) {
				Cmm::setYPixel((unsigned char)diff, (i % Width) + (j * Width), YuvBuffer, width, height);
			} else {
				Yuv4::setYPixel((unsigned char )diff, (i % Width) + (j * Width), YuvBuffer, width, height);
			}
		}
	}

	return;
}
void YuvDiff::GetRgb(uint8_t *rgbbuf)
{
	if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
		RawVideo420::getRgb(YuvBuffer, Width, Height, rgbbuf, TRUE, TRUE, TRUE);
	} else if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_CMM) {
		Cmm::getRgb(YuvBuffer, Width, Height, rgbbuf, TRUE, TRUE, TRUE);
	} else {
		Yuv4::getRgb(YuvBuffer, Width, Height, rgbbuf, TRUE, TRUE, TRUE);
	}
	return;
}

void YuvDiff::SetDiffTimes(int times)
{
	Times = times;
	return;
}
int YuvDiff::GetDiffTimes(void)
{
	return Times;
}

void YuvDiff::SetSize(uint32_t width, uint32_t height)
{
	int size;
	if (YuvBuffer != NULL) {
		free(YuvBuffer);
	}
	if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YUV4) {
		size = Yuv4::getFrameBufferSize(width, height);
	}
	else if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_CMM) {
		size = Cmm::getFrameBufferSize(width, height);
	}
	else {
		size = 0;
	}

	YuvBuffer = (uint8_t *)malloc(size);
	if (YuvBuffer == NULL) {
		Win32Printf("%hs %d malloc error", __func__, __LINE__);
		return;
	}
	memset(YuvBuffer, 0x00, size);

	return;
}


