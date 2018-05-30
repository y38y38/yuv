#include "stdafx.h"

#include "stdlib.h"

#include "yuv_debug.h"

#include "window_manager.h"

#include "yuv_reciever.h"

YuvReciever::YuvReciever(void)
{
	RgbBuf[1] = NULL;
	return;
}

YuvReciever::~YuvReciever(void)
{
	return;
}
void YuvReciever::SetRgbBufSize(void)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	if (RgbBuf != NULL) {
		free(RgbBuf);
	}
	RgbBuf = (uint8_t*)malloc(width * height * 3);
	if (RgbBuf == NULL) {
		Win32Printf("%hs %d malloc error", __FUNCTION__, __LINE__);
		//エラー処理
	}

	return;
}

void YuvReciever::UpdateImage(void)
{
	Win32Printf("%hs %d", __FUNCTION__, __LINE__);
	WindowManager::GetInst().Update();
	return;
}


void YuvReciever::SetPixel(YuvSetting::YuvSize size)
{
	YuvSetting::GetInst().SetSize(size);


	//画像サイズが変更されたらバッファサイズを変更する必要がある。
	SetRgbBufSize();

	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	//画像サイズが変更されたら画像の更新も行う。
	UpdateImage();
	return;
}

uint32_t YuvReciever::GetWidthSize(void)
{
	if (YuvSetting::GetInst().GetView() == YuvSetting::YUV_VIEW_SINGLE) {
		return 	YuvSetting::GetInst().GetWidthSize();
	}
	else {
		return 	(YuvSetting::GetInst().GetWidthSize() * 2);
	}

}
uint32_t YuvReciever::GetHeightSize(void)
{
	return	YuvSetting::GetInst().GetHeightSize();
}
void YuvReciever::SetFormat(YuvSetting::YuvFormat format)
{
	YuvSetting::GetInst().SetFormat(format);

	WindowManager::GetInst().Update();
	return;
}
YuvSetting::YuvFormat YuvReciever::GetFormat(void)
{
	return YuvSetting::GetInst().GetFormat();
}


uint8_t *YuvReciever::GetRgbBuf(void)
{
	return RgbBuf;
}
void YuvReciever::Init(void)
{
	YuvSetting::GetInst().InitSetting();
	SetRgbBufSize();

	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = (int)YuvSetting::GetInst().GetHeightSize();


	return;
}
void YuvReciever::SetView(YuvSetting::YuvView view)
{
	YuvSetting::GetInst().SetView(view);
	WindowManager::GetInst().Update();
	return;
}

YuvSetting::YuvView YuvReciever::GetView(void)
{
	return YuvSetting::GetInst().GetView();
}


