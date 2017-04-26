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

