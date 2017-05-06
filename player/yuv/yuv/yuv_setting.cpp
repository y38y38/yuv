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
	else {
		return 1920;
	}
}

uint32_t YuvSetting::GetHeightSize(void)
{
	if (Size == YUV_SIZE_352_288) {
		return 288;
	}
	else {
		return 1080;
	}
}
void YuvSetting::InitSetting(void)
{
	Format = YUV_FORMAT_YV12;
	Size = YUV_SIZE_352_288;
	View = YUV_VIEW_SINGLE;
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

