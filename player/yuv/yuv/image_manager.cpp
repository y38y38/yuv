#include "stdafx.h"

#include "stdio.h"

#include "stdlib.h"
#include "stdint.h"

#include "image_manager.h"

#include "filebuffer.h"

#include "rawvideo420.h"
#include "yuv4.h"
#include "yuv_setting.h"

#define	CACHE_MEMORY_SIZE (0)

ImageManager::ImageManager()
{
	FrameNumber = 0;
	return;
}
ImageManager::~ImageManager()
{
	return;
}
void ImageManager::Init(TCHAR *filename)
{
	Buffer.create(filename, CACHE_MEMORY_SIZE);

}
void ImageManager::Update(int frame_number, uint32_t width, uint32_t height, uint8_t *rgb_buf)
{
	int yuv_offset = 0;
	int framesize = getFrameBufferSize(width, height);
	uint8_t *yuv_buffer = (uint8_t *)malloc(framesize);
	if (yuv_buffer == NULL) {
		return;
	}

	unsigned long ret;
	yuv_offset = framesize * frame_number;
	Buffer.read(yuv_buffer, yuv_offset, framesize, &ret);

	if (framesize != ret) {
		//ñ{ìñÇÕÉGÉâÅ[èàóù
		free(yuv_buffer);
		return;
	}
	GetRgb(yuv_buffer, width, height, rgb_buf);

	free(yuv_buffer);
	FrameNumber = frame_number;
	return;
}
void ImageManager::GetRgb(uint8_t *yuvbuffer, uint32_t width, uint32_t height, uint8_t *rgb_buf)
{

	if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
		RawVideo420::getRgb(yuvbuffer, width, height, rgb_buf, TRUE, TRUE, TRUE);
	}
	else {
		Yuv4::getRgb(yuvbuffer, width, height, rgb_buf, TRUE, TRUE, TRUE);
	}
	return;
}
int ImageManager::getFrameBufferSize(uint32_t width, uint32_t height)
{
	if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
		return RawVideo420::getFrameBufferSize(width, height);
	}
	else {
		return Yuv4::getFrameBufferSize(width, height);
	}
}
uint32_t ImageManager::GetFrameNumber(void)
{
	return FrameNumber;
}

