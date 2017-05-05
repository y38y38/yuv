#include "stdafx.h"

#include "yuv_player.h"


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

	return;
}

uint8_t *YuvPlayer::GetRgbBuf(void)
{
	return rgb_buf;
}

