#include "stdafx.h"

#include "stdlib.h"

#include "yuv_debug.h"

#include "window_manager.h"

#include "rgb_utility.h"

#include "yuv_player.h"


YuvPlayer::YuvPlayer(void)
{
	FileNum = 0;
	SingleViewIndex = 0;
	for (int i = 0; i < MAX_FILE_NUM; i++) {
		RgbBuf[i] = NULL;
	}
	MultiRgbBuf = NULL;

	return;
}

YuvPlayer::~YuvPlayer(void)
{
	return;
}

void YuvPlayer::SetRgbBuf(void)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	for (int i = 0; i < MAX_FILE_NUM; i++) {
		if (RgbBuf[i] != NULL) {
			free(RgbBuf[i]);
		}
		RgbBuf[i] = (uint8_t*)malloc(width * height * 3);
		if (RgbBuf[i] == NULL) {
			Win32Printf("%hs %d malloc error", __FUNCTION__, __LINE__);
			//エラー処理
		}
	}

	if (MultiRgbBuf != NULL) {
		free(MultiRgbBuf);
	}
	MultiRgbBuf = (uint8_t*)malloc(width * height * 3 * MAX_FILE_NUM);
	if (MultiRgbBuf == NULL) {
		Win32Printf("%hs %d malloc error", __FUNCTION__, __LINE__);
		//エラー処理
	}
	return;
}
void YuvPlayer::UpdateImage(int image_index, int frame_number)
{
	Img[image_index].Update(frame_number, RgbBuf[image_index]);

	WindowManager::GetInst().Update();
	return;
}
void YuvPlayer::SetPixel(YuvSetting::YuvSize size)
{
	YuvSetting::GetInst().SetSize(size);
	//画像サイズが変更されたらバッファサイズを変更する必要がある。
	SetRgbBuf();

	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	for (int i = 0; i < MAX_FILE_NUM; i++) {
		Img[i].SetSize(width, height);

		//画像サイズが変更されたら画像の更新も行う。
		uint32_t frame_number = Img[i].GetFrameNumber();
		UpdateImage(i, frame_number);
	}
	Diff.SetSize(width, height);
	return;
}
uint32_t YuvPlayer::GetWidthSize(void)
{
	if (YuvSetting::GetInst().GetView() == YuvSetting::YUV_VIEW_SINGLE) {
		return 	YuvSetting::GetInst().GetWidthSize();
	}
	else {
		return 	(YuvSetting::GetInst().GetWidthSize() * 2);
	}

}
uint32_t YuvPlayer::GetHeightSize(void)
{
	if (YuvSetting::GetInst().GetView() == YuvSetting::YUV_VIEW_SINGLE) {
		return	YuvSetting::GetInst().GetHeightSize();
	}
	else {
		if (FileNum > 2) {
			return	(YuvSetting::GetInst().GetHeightSize() * 2);
		}
		else {
			return	YuvSetting::GetInst().GetHeightSize();
		}

	}
}

void YuvPlayer::InputFile(TCHAR *filename)
{
	int index = FileNum % MAX_FILE_NUM;
	Img[index].Init(filename);
	int width = (int)YuvSetting::GetInst().GetWidthSize();
	int height = (int)YuvSetting::GetInst().GetHeightSize();
	Img[index].SetSize(width, height);
	Diff.SetSize(width, height);

	UpdateImage(index, 0);

	SingleViewIndex = index;

	FileNum++;
	return;
}

uint8_t *YuvPlayer::GetRgbBuf(void)
{
	if (YuvSetting::GetInst().GetView() == YuvSetting::YUV_VIEW_SINGLE) {
		return RgbBuf[SingleViewIndex];
	}
	else {
#if 1
		if (IsImageDiff() == true) {
			uint8_t * img0 = Img[0].GetYuvBuf();
			uint8_t * img1 = Img[1].GetYuvBuf();
			Diff.CreateDiff(img0, img1);
			Diff.GetRgb(RgbBuf[1]);

		}
#endif
		int width = (int)YuvSetting::GetInst().GetWidthSize();
		int height = (int)YuvSetting::GetInst().GetHeightSize();

		int file_num = FileNum % MAX_FILE_NUM;

		RgbUtility::RgbCombine(width, height, file_num, RgbBuf, MultiRgbBuf);
		return MultiRgbBuf;
	}
}
void YuvPlayer::Init(void)
{
	YuvSetting::GetInst().InitSetting();
	SetRgbBuf();
	return;
}
int YuvPlayer::GetFileNum(void)
{
	int file_num;
	if (FileNum > MAX_FILE_NUM) {
		file_num = MAX_FILE_NUM;
	}
	else {
		file_num = FileNum;
	}
	return file_num;

}


void YuvPlayer::NextFrame(void)
{
	uint32_t frame_number;
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		frame_number = Img[i].GetFrameNumber() + 1;
		UpdateImage(i, frame_number);
	}
	Win32Printf("%d", frame_number);
	return;
}
void YuvPlayer::PrevFrame(void)
{
	uint32_t frame_number;
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		frame_number = Img[i].GetFrameNumber();
		if (frame_number != 0) {
			UpdateImage(i, frame_number - 1 );
		}
	}
	Win32Printf("%d", frame_number);
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
	int file_num = GetFileNum();

	SingleViewIndex++;
	if (SingleViewIndex >= file_num) {
		SingleViewIndex = 0;
	} else {
		SingleViewIndex = SingleViewIndex % MAX_FILE_NUM;
	}

	WindowManager::GetInst().Update();
	return;
}

void YuvPlayer::PrevImage(void)
{
	int file_num = GetFileNum();
	if (SingleViewIndex != 0) {
		SingleViewIndex--;
	} else {
		SingleViewIndex = file_num - 1;
	}
	WindowManager::GetInst().Update();
	return;
}
void YuvPlayer::SetDiffMode(YuvSetting::YuvDiffMode diff)
{
	YuvSetting::GetInst().SetDiffMode(diff);

}
YuvSetting::YuvDiffMode YuvPlayer::GetDiffMode(void)
{
	return YuvSetting::GetInst().GetDiffMode();
}
bool YuvPlayer::IsImageDiff(void)
{
	YuvSetting::YuvDiffMode mode = YuvSetting::GetInst().GetDiffMode();
	if (mode == YuvSetting::YUV_DIFF_DISABLE) {
		return false;
	}
	else if (mode == YuvSetting::YUV_DIFF_ENABLE) {
		return true;
	}
	else {
		if (OnMouse == true) {
			return true;
		}
		else {
			return false;
		}
	}
}
void YuvPlayer::SetMouse(void) {
	OnMouse = true;
	return;
}

void YuvPlayer::ReleaseMouse(void) {
	OnMouse = false;
	return;
}
