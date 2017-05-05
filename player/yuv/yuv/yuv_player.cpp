#include "stdafx.h"

#include "stdlib.h"

#include "yuv_player.h"

#include "window_manager.h"

YuvPlayer::YuvPlayer(void)
{
	return;
}

YuvPlayer::~YuvPlayer(void)
{
	return;
}

void YuvPlayer::SetPixel(YuvSetting::YuvSize size)
{
	YuvSetting::GetInst().SetSize(size);
	return;
}
uint32_t YuvPlayer::GetWidthSize(void)
{
	return 	YuvSetting::GetInst().GetWidthSize();

}
uint32_t YuvPlayer::GetHeightSize(void)
{
	return	YuvSetting::GetInst().GetHeightSize();
}

void YuvPlayer::InputFile(TCHAR *filename)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	Img.Init(filename);
	Img.Update(0, width, height, rgb_buf);
	WindowManager::GetInst().Update();
	return;
}

uint8_t *YuvPlayer::GetRgbBuf(void)
{
	return rgb_buf;
}
void YuvPlayer::Init(void)
{
#define RGB_BUF_MAX (4096*2160*3*2) /* 4K(4096x2160) RGB (x3) 16bit (x2) */
	rgb_buf = (uint8_t*)malloc(RGB_BUF_MAX);
	if (rgb_buf) {
		//ÉGÉâÅ[èàóù
	}

	YuvSetting::GetInst().InitSetting();

	return;
}

void YuvPlayer::NextFrame(void)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();
	uint32_t frame_number = Img.GetFrameNumber() + 1;
	Img.Update(frame_number, width, height, rgb_buf);
	WindowManager::GetInst().Update();
	return;
}
void YuvPlayer::PrevFrame(void)
{
	uint32_t frame_number = Img.GetFrameNumber();
	if (frame_number != 0) {
		uint32_t width = YuvSetting::GetInst().GetWidthSize();
		uint32_t height = YuvSetting::GetInst().GetHeightSize();
		Img.Update(frame_number - 1, width, height, rgb_buf);
		WindowManager::GetInst().Update();
	}
	return;
}

