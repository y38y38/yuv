#pragma once
#ifndef _YUV_SETTING_H_
#define _YUV_SETTING_H_
#include <stdint.h>

class YuvSetting {
public:
	static YuvSetting& GetInst(void) {
		static YuvSetting singleton;
		return singleton;
	}
	void InitSetting(void);
	typedef enum {
		YUV_FORMAT_YV12,
		YUV_FORMAT_YUV4,
		YUV_FORMAT_CMM,
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

	typedef enum {
		YUV_VIEW_SINGLE,
		YUV_VIEW_SIDE_BY_SIDE,
	} YuvView;
	void SetView(YuvView view);
	YuvView GetView(void);

	typedef enum {
		YUV_DIFF_DISABLE,
		YUV_DIFF_ENABLE,
		YUV_DIFF_ONMOUSE,
	} YuvDiffMode;
	void SetDiffMode(YuvDiffMode diff);
	YuvDiffMode GetDiffMode(void);


	typedef enum {
		YUV_DIFFTIMES_X1,
		YUV_DIFFTIMES_X10,
	} YuvDiffTimes;
	void SetDiffTimes(YuvDiffTimes times);
	uint32_t GetDiffTimes(void);

	void SetSignalY(bool y);
	void SetSignalCb(bool cb);
	void SetSignalCr(bool cr);

	bool GetSignalY(void);
	bool GetSignalCb(void);
	bool GetSignalCr(void);

private:
	YuvSetting();
	~YuvSetting();

	YuvFormat Format;
	YuvSize Size;
	YuvView View;
	YuvDiffMode DiffMode;
	YuvDiffTimes DiffTimes;

	bool SignalY;
	bool SignalCb;
	bool SignalCr;
};

#endif //_YUV_SETTING_H



