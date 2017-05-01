#pragma once
#ifndef _YUV_SETTING_H
#define _YUV_SETTING_H
#include <stdint.h>

class YuvSetting {
public:
	//static YuvSetting *GetInst(void);
	static YuvSetting& GetInst(void) {
		static YuvSetting singleton;
		return singleton;
	}
	void InitSetting(void);
	typedef enum {
		YUV_FORMAT_YV12,
		YUV_FORMAT_YUV4,
	} YuvFormat;
	void SetFormat(YuvFormat format);
	YuvFormat GetFormat(void);

	typedef enum {
		YUV_SIZE_352_288,
		YUV_SIZE_1920_1080,
	} YuvSize;
	void SetSize(YuvSize size);
	YuvSize GetSize(void);
	uint32_t GetWidthSize(void);
	uint32_t GetHeightSize(void);
private:
	YuvSetting();
	~YuvSetting();

	//static YuvSetting Instance;
#if 1
	YuvFormat Format;
	YuvSize Size;
#endif
};

#endif //_YUV_SETTING_H


