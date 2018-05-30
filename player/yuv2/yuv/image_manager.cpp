#include "stdafx.h"

#include "stdio.h"

#include "stdlib.h"
#include "stdint.h"

#include "image_manager.h"

#include "filebuffer.h"

#include "rawvideo420.h"
#include "yuv4.h"
#include "cmm.h"

#include "yuv_setting.h"

#include "yuv_debug.h"

#define	CACHE_MEMORY_SIZE (0)

ImageManager::ImageManager()
{
	FrameNumber = 0;
	YuvBuffer = NULL;
	SignalY = true;
	SignalCb = true;
	SignalCr = true;

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
void ImageManager::UpdateYuv(int frame_number)
{
	int yuv_offset = 0;
	unsigned long ret;
	int framesize = getFrameBufferSize(Width, Height);
	yuv_offset = framesize * frame_number;
	Buffer.read(YuvBuffer, yuv_offset, framesize, &ret);

	if (framesize != ret) {
		//ñ{ìñÇÕÉGÉâÅ[èàóù
		Win32Printf("%hs %d read error\n", __func__, __LINE__)
	    return;
	}

	FrameNumber = frame_number;
	return;
}
void ImageManager::SetRgbBuf(uint8_t *rgb_buf)
{
	GetRgb(YuvBuffer, Width, Height, rgb_buf);
}
void ImageManager::Update(int frame_number, uint8_t *rgb_buf)
{
	UpdateYuv(frame_number);
	SetRgbBuf(rgb_buf);

	return;
}
void ImageManager::GetRgb(uint8_t *yuvbuffer, uint32_t width, uint32_t height, uint8_t *rgb_buf)
{

	if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
		RawVideo420::getRgb(yuvbuffer, width, height, rgb_buf, SignalY, SignalCb, SignalCr);
	}
	else if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_CMM) {
		Cmm::getRgb(yuvbuffer, width, height, rgb_buf, SignalY, SignalCb, SignalCr);
	} else {
		Yuv4::getRgb(yuvbuffer, width, height, rgb_buf, SignalY, SignalCb, SignalCr);
	}
	return;
}
int ImageManager::getFrameBufferSize(uint32_t width, uint32_t height)
{
	if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
		return RawVideo420::getFrameBufferSize(width, height);
	} else if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_CMM) {
		return Cmm::getFrameBufferSize(width, height);

	} else {
		return Yuv4::getFrameBufferSize(width, height);
	}
}
uint32_t ImageManager::GetFrameNumber(void)
{
	return FrameNumber;
}

void ImageManager::SetSize(uint32_t width, uint32_t height)
{
	if (YuvBuffer != NULL) {
		free(YuvBuffer);
	}

	Width = width;
	Height = height;
	int framesize = getFrameBufferSize(width, height);
	YuvBuffer = (uint8_t *)malloc(framesize);
	if (YuvBuffer == NULL) {
		Win32Printf("%hs %d read error\n", __func__, __LINE__)
	}

	return;
}
uint8_t *ImageManager::GetYuvBuf(void)
{
	return YuvBuffer;
}


TCHAR *ImageManager::GetFileName(void)
{

	return Buffer.getFileName();
}

void ImageManager::SetSignalY(bool y)
{
	SignalY = y;
}

void ImageManager::SetSignalCb(bool cb)
{
	SignalCb = cb;

}
void ImageManager::SetSignalCr(bool cr)
{
	SignalCr = cr;

}
