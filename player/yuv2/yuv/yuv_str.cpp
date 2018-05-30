#include "stdafx.h"

#include "yuv_str.h"

YuvStr::YuvStr(void)
{
	return;
}

YuvStr::~YuvStr(void)
{
	return;
}

TCHAR *YuvStr::GetFileName(TCHAR *path)
{
	TCHAR *result;
	TCHAR *next;

	next = path;
	for (int i=0;i<100;i++) {
		result = _tcsstr(next, _T("\\"));
		if (result == NULL) {
			break;
		}
		result++;
		next = result;
	}

	return next;
}

