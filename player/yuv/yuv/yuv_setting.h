#pragma once

class YuvSetting {
public:
	YuvSetting();
	~YuvSetting();

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


private:
	YuvFormat Format;
	YuvSize Size;
};


