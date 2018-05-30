#include "stdafx.h"

#include "yuv_setting.h"


YuvSetting::YuvSetting()
{
	return;
}
YuvSetting::~YuvSetting()
{
	return;
}
void YuvSetting::SetFormat(YuvFormat format)
{	
	Format = format;
	return;
}

YuvSetting::YuvFormat YuvSetting::GetFormat(void)
{
	return Format;
}

void YuvSetting::SetSize(YuvSize size)
{
	Size = size;
	return;
}

YuvSetting::YuvSize YuvSetting::GetSize(void)
{
	return Size;
}
uint32_t YuvSetting::GetWidthSize(void)
{
	if (Size == YUV_SIZE_352_288) {
		return 352;
	}
	else if (Size == YUV_SIZE_720_480) {
		return 720;
	}
	else {
		return 1920;
	}
}

uint32_t YuvSetting::GetHeightSize(void)
{
	if (Size == YUV_SIZE_352_288) {
		return 288;
	}
	else if (Size == YUV_SIZE_720_480) {
		return 480;
	}
	else {
		return 1080;
	}
}
void YuvSetting::InitSetting(void)
{
	Format = YUV_FORMAT_CMM;
	Size = YUV_SIZE_352_288;
	Size = YUV_SIZE_720_480;
	View = YUV_VIEW_SINGLE;
	DiffMode = YUV_DIFF_DISABLE;
	DiffTimes = YUV_DIFFTIMES_X1;
	SignalY = true;
	SignalCb = true;
	SignalCr = true;

	return;
}
void YuvSetting::SetView(YuvView view)
{
	View = view;
	return;
}
YuvSetting::YuvView YuvSetting::GetView(void)
{
	return View;
}

void YuvSetting::SetDiffMode(YuvDiffMode diffmode)
{
	DiffMode = diffmode;
	return;
}
YuvSetting::YuvDiffMode YuvSetting::GetDiffMode(void)
{
	return DiffMode;
}
void YuvSetting::SetDiffTimes(YuvDiffTimes times)
{
	DiffTimes = times;
	return;
}

uint32_t YuvSetting::GetDiffTimes(void)
{
	if (DiffTimes == YUV_DIFFTIMES_X1) {
		return 1;
	}
	else {
		return 10;

	}
}

void YuvSetting::SetSignalY(bool y)
{
	SignalY = y;
}
bool YuvSetting::GetSignalY(void)
{
	return SignalY;
}
void YuvSetting::SetSignalCb(bool cb)
{
	SignalCb = cb;
}
bool YuvSetting::GetSignalCb(void)
{
	return SignalCb;
}
void YuvSetting::SetSignalCr(bool cr)
{
	SignalCr = cr;
}
bool YuvSetting::GetSignalCr(void)
{
	return SignalCr;
}



