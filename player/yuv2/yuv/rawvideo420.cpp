#include "stdafx.h"
#include "yuvrgb.h"

#include "RawVideo420.h"


RawVideo420::RawVideo420(void) {

}
RawVideo420::~RawVideo420(void) {
}

int RawVideo420::getFrameBufferSize(int width, int height)
{
	if (width == 0) return 0; //0èúéZëŒçÙ
	if (height == 0) return 0;//0èúéZëŒçÙ

	return ((width * height) + ((width * height) / 2));
}


int RawVideo420::getRgb(unsigned char *ypbpr_buffer, int width, int height, unsigned char *output_rgb_buffer, BOOL enable_y, BOOL enable_pb, BOOL enable_pr) {
	unsigned char *rgb_buffer = output_rgb_buffer;
	short y, pb, pr;
	static short test_buffer[3 * 1024 * 1024];

	memset(rgb_buffer, 0x0, (width * height) * 3);
	for (int i = 0; i < (width*height); i++) {
		getPixel(ypbpr_buffer, i, &y, &pb, &pr, width, height);
		test_buffer[i] = pb;
		if (enable_y != TRUE) {
			y = 128;
		}
		if (enable_pb != TRUE) {
			pb = 128;
		}
		if (enable_pr != TRUE) {
			pr = 128;
		}
#if 0
		YuvRgb *yuvrgbp = new YuvRgb();
		yuvrgbp->ypbpr2rgb(y, pb, pr, rgb_buffer);
#else
		YuvRgb::ypbpr2rgb(y, pb, pr, rgb_buffer);
#endif

		rgb_buffer += 3;
	}

	return 0;
}

int RawVideo420::signalValid(unsigned char *ypbpr_buffer, int pixel, BOOL enable_y, BOOL enable_pb, BOOL enable_pr) {
	return 0;
}

int RawVideo420::signalConvert(unsigned char *ypbpr_buffer, int pixel, enum img_convert convert) {
	return 0;
}
void RawVideo420::getPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr, int max_width , int  max_height) {
	int width = pixel % max_width;
	int height;
	if (pixel !=0 ) {
		height = pixel / max_width;
	}
	else {
		height = 0;
	}
	*y = *(buffer + pixel);

	if (width == 0) width = 1;//0èúéZñhé~
	if (height == 0) height = 1;//0èúéZñhé~

	*pb = *(buffer + (max_width * max_height) + ((width / 2) + ((height / 2) * (max_width/2))));
	*pr = *(buffer + (max_width * max_height) + ((max_width / 2) * (max_height / 2)) + ((width / 2) +  ((height / 2) * (max_width/2))));
	return;
}

void RawVideo420::getYPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr) {
		*y = *(buffer + pixel);
}

void RawVideo420::setPixel(short y, short pb, short pr, int pixel, unsigned char *buffer) {}
void RawVideo420::setYPixel(short y, int pixel, unsigned char *buffer) {}
