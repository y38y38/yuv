#include "stdafx.h"

#include "stdlib.h"

#include "yuv_player.h"

#include "window_manager.h"

YuvPlayer::YuvPlayer(void)
{
	FileNum = 0;
	SingleViewIndex = 0;
	for (int i = 0; i < MAX_FILE_NUM; i++) {
		RgbBuf[i] = NULL;
	}

	return;
}

YuvPlayer::~YuvPlayer(void)
{
	return;
}

void YuvPlayer::UpdateRgbBuf(void)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	for (int i = 0; i < MAX_FILE_NUM; i++) {
		if (RgbBuf[i] != NULL) {
			free(RgbBuf[i]);
		}
		RgbBuf[i] = (uint8_t*)malloc(width * height * 3);
		if (RgbBuf[i] == NULL) {
			//エラー処理
		}
	}
	return;
}
void YuvPlayer::SetPixel(YuvSetting::YuvSize size)
{
	YuvSetting::GetInst().SetSize(size);
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	UpdateRgbBuf();

	for (int i = 0; i < MAX_FILE_NUM; i++) {
		Img[i].Update(0, width, height, RgbBuf[i]);
	}
	WindowManager::GetInst().Update();
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

	int index = FileNum % MAX_FILE_NUM;
	Img[index].Init(filename);
	wchar_t msg[32];
	swprintf_s(msg, L"rgb=%x \n", RgbBuf[index]);
	OutputDebugString(msg);
	Img[index].Update(0, width, height, RgbBuf[index]);
	SingleViewIndex = index;

	FileNum++;

	WindowManager::GetInst().Update();
	return;
}

uint8_t *YuvPlayer::GetRgbBuf(void)
{
	return RgbBuf[SingleViewIndex];
}
void YuvPlayer::Init(void)
{
	YuvSetting::GetInst().InitSetting();
	UpdateRgbBuf();
	return;
}

void YuvPlayer::NextFrame(void)
{
	int file_num;
	if (FileNum > MAX_FILE_NUM) {
		file_num = MAX_FILE_NUM;
	} else {
		file_num = FileNum;
	}
	for (int i = 0; i < file_num; i++) {
		uint32_t width = YuvSetting::GetInst().GetWidthSize();
		uint32_t height = YuvSetting::GetInst().GetHeightSize();
		uint32_t frame_number = Img[i].GetFrameNumber() + 1;
		Img[i].Update(frame_number, width, height, RgbBuf[SingleViewIndex]);
		WindowManager::GetInst().Update();
	}

	return;
}
void YuvPlayer::PrevFrame(void)
{
	int file_num;
	if (FileNum > MAX_FILE_NUM) {
		file_num = MAX_FILE_NUM;
	}
	else {
		file_num = FileNum;
	}
	for (int i = 0; i < file_num; i++) {
		uint32_t frame_number = Img[i].GetFrameNumber();
		if (frame_number != 0) {
			uint32_t width = YuvSetting::GetInst().GetWidthSize();
			uint32_t height = YuvSetting::GetInst().GetHeightSize();
			Img[i].Update(frame_number - 1, width, height, RgbBuf[SingleViewIndex]);
			WindowManager::GetInst().Update();
		}
	}
	return;
}
void YuvPlayer::SetView(YuvSetting::YuvView view)
{
	YuvSetting::GetInst().SetView(view);
	return;
}

YuvSetting::YuvView YuvPlayer::GetView(void)
{
	return YuvSetting::GetInst().GetView();
}
void YuvPlayer::NextImage(void)
{
	return;
}

void YuvPlayer::PrevImage(void)
{
	return;
}
