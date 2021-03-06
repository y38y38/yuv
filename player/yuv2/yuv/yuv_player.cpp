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

	DiffPosition = YUV_WINDOW_LEFT_TOP;

	return;
}

YuvPlayer::~YuvPlayer(void)
{
	return;
}

void YuvPlayer::SetRgbBufSize(void)
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
void YuvPlayer::UpdateImageAll(int frame_number)
{
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		UpdateImage(i, frame_number);
	}

	return;
}

void YuvPlayer::UpdateImage(int image_index, int frame_number)
{
	Win32Printf("%hs %d frame_number %d", __FUNCTION__, __LINE__, frame_number);
	Img[image_index].Update(frame_number, RgbBuf[image_index]);

	WindowManager::GetInst().Update();
	return;
}
void YuvPlayer::SetPixel(YuvSetting::YuvSize size)
{
	YuvSetting::GetInst().SetSize(size);


	//画像サイズが変更されたらバッファサイズを変更する必要がある。
	SetRgbBufSize();

	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	for (int i = 0; i < MAX_FILE_NUM; i++) {
		Img[i].SetSize(width, height);

		//画像サイズが変更されたら画像の更新も行う。
		uint32_t frame_number = Img[i].GetFrameNumber();
		UpdateImage(i, frame_number);
	}
	Diff.SetSize(width, height);

	WindowManager::GetInst().Update();
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
void YuvPlayer::SetFormat(YuvSetting::YuvFormat format)
{
	YuvSetting::GetInst().SetFormat(format);

	WindowManager::GetInst().Update();
	return;
}
YuvSetting::YuvFormat YuvPlayer::GetFormat(void)
{
	return YuvSetting::GetInst().GetFormat();
}


void YuvPlayer::InputFile(TCHAR *filename)
{
	int index = FileNum % MAX_FILE_NUM;
	Img[index].Init(filename);
	Img[index].SetSignalY(YuvSetting::GetInst().GetSignalY());
	Img[index].SetSignalCb(YuvSetting::GetInst().GetSignalCb());
	Img[index].SetSignalCr(YuvSetting::GetInst().GetSignalCr());
	UpdateImage(index, 0);

	SingleViewIndex = index;

	FileNum++;

	WindowManager::GetInst().Update();
	return;
}

uint8_t *YuvPlayer::GetRgbBuf(void)
{
	if (YuvSetting::GetInst().GetView() == YuvSetting::YUV_VIEW_SINGLE) {
		return RgbBuf[SingleViewIndex];
	}
	else {
		if (IsImageDiff() == true) {
			uint8_t * img0 = Img[0].GetYuvBuf();
			uint8_t * img1 = Img[1].GetYuvBuf();
			Diff.CreateDiff(img0, img1);
			Diff.GetRgb(RgbBuf[DiffPosition % MAX_FILE_NUM]);

		}
		//diff enable->disableの時は↑で、RgbBuf[1]を上書きしているので、もう一度RGBを生成する必要がある。
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
	SetRgbBufSize();

	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = (int)YuvSetting::GetInst().GetHeightSize();

	Diff.SetSize(width, height);
	Diff.SetDiffTimes(YuvSetting::GetInst().GetDiffTimes());

	for (int i = 0; i < MAX_FILE_NUM; i++) {
		Img[i].SetSize(width, height);
	}

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
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		uint32_t  frame_number = Img[i].GetFrameNumber() + 1;
		UpdateImage(i, frame_number);
	}
	WindowManager::GetInst().Update();
	return;
}
void YuvPlayer::PrevFrame(void)
{
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		uint32_t frame_number = Img[i].GetFrameNumber();
		if (frame_number != 0) {
			UpdateImage(i, frame_number - 1 );
		}
	}
	WindowManager::GetInst().Update();
	return;
}
void YuvPlayer::JumpFrame(int frame)
{
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		uint32_t frame_number = Img[i].GetFrameNumber();
		if (frame_number != 0) {
			UpdateImage(i, frame_number + frame);
		}
	}
	WindowManager::GetInst().Update();
	return;
}

void YuvPlayer::SetView(YuvSetting::YuvView view)
{
	YuvSetting::GetInst().SetView(view);
	WindowManager::GetInst().Update();
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

	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		uint32_t  frame_number = Img[i].GetFrameNumber();
		UpdateImage(i, frame_number);
	}

	WindowManager::GetInst().Update();
	return;
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
void YuvPlayer::SetMouse(YUV_WINDOW_POS pos) {
	if (OnMouse == false) {
		UpdateRgbBuf();
	}
	else if (DiffPosition != pos) {
		UpdateRgbBuf();
	}

	OnMouse = true;
	DiffPosition = pos;
	return;
}

void YuvPlayer::ReleaseMouse(void) {
	if (OnMouse == true) {
		UpdateRgbBuf();
	}
	OnMouse = false;
	return;
}
void YuvPlayer::SetDiffTimes(YuvSetting::YuvDiffTimes times)
{
	YuvSetting::GetInst().SetDiffTimes(times);

	Diff.SetDiffTimes(YuvSetting::GetInst().GetDiffTimes());

	WindowManager::GetInst().Update();
	return;
}
int YuvPlayer::GetDiffTimes(void)
{
	return YuvSetting::GetInst().GetDiffTimes();
}

void YuvPlayer::UpdateRgbBuf()
{
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		Img[i].SetRgbBuf(RgbBuf[i]);

	}
	WindowManager::GetInst().Update();

}

TCHAR *YuvPlayer::GetFileName(int file_index)
{
	return Img[file_index].GetFileName();
}

void YuvPlayer::SetSignalY(bool y)
{
	YuvSetting::GetInst().SetSignalY(y);
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		Img[i].SetSignalY(y);
	}

}
void YuvPlayer::SetSignalCb(bool cb)
{
	YuvSetting::GetInst().SetSignalCb(cb);
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		Img[i].SetSignalCb(cb);
	}

}
void YuvPlayer::SetSignalCr(bool cr)
{
	YuvSetting::GetInst().SetSignalCr(cr);
	int file_num = GetFileNum();
	for (int i = 0; i < file_num; i++) {
		Img[i].SetSignalCr(cr);
	}

}
bool YuvPlayer::GetSignalY(void)
{
	return YuvSetting::GetInst().GetSignalY();
}
bool YuvPlayer::GetSignalCb(void)
{
	return YuvSetting::GetInst().GetSignalCb();

}
bool YuvPlayer::GetSignalCr(void)
{
	return YuvSetting::GetInst().GetSignalCr();

}

int YuvPlayer::GetViewIndex(void)
{
	return SingleViewIndex;
}

