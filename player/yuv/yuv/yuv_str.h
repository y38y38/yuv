#pragma once

#ifndef _YUV_STR_H_
#define _YUV_STR_H_

#include "tchar.h"

class YuvStr {
public:
	YuvStr();
	~YuvStr();
	static TCHAR* GetFileName(TCHAR *path);
private:
};
#endif // _YUV_STR_H_


