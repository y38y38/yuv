#pragma once

#include "stdafx.h"

//rawvideo420 4:2:0 8bit


class RawVideo420 {
public:
	RawVideo420(void);
	 ~RawVideo420(void);

	static int getRgb(unsigned char *ypbpr_buffer, int width, int heght, unsigned char *output_rgb_buffer, BOOL enable_y, BOOL enable_pb, BOOL enable_pr);

	static int signalValid(unsigned char *ypbpr_buffer, int pixel, BOOL enable_y, BOOL enable_pb, BOOL enable_pr);

	static int signalConvert(unsigned char *ypbpr_buffer, int pixel, enum img_convert convert);
	static void getPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr, int width, int height);
	static void getYPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr);

	static void setPixel(short y, short pb, short pr, int pixel, unsigned char *buffer);
	static void setYPixel(short y, int pixel, unsigned char *buffer);

	static int getFrameBufferSize(int width, int height);
private:
	static void ypbpr2rgb(short y, short pb, short pr, unsigned char *rgb);
};

