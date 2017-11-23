#include "stdafx.h"

#include "YuvRgb.h"

#include "Cmm.h"


int Cmm::getFrameBufferSize(int width, int height)
{
	if (width == 0) return 0; //0èúéZëŒçÙ
	if (height == 0) return 0;//0èúéZëŒçÙ
	return (((width * height) * 2) + (((width / 2) * (height / 2)) * 4));

}

int Cmm::getRgb(unsigned char *ypbpr_buffer, int width, int height, unsigned char *output_rgb_buffer, BOOL enable_y, BOOL enable_pb, BOOL enable_pr)
{
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
		YuvRgb::ypbpr2rgb(y, pb, pr, rgb_buffer);

		rgb_buffer += 3;
	}
	return 0;
}
void Cmm::getPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr, int max_width, int  max_height) {
	//pointer is short
	getYPixel(buffer, pixel, y, pb, pr, max_width, max_height);
	getPbPixel(buffer, pixel, pb, max_width, max_height);
	getPrPixel(buffer, pixel, pr, max_width, max_height);
	return;
}
void Cmm::getYPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr, int max_width, int max_height)
{
	//pointer is short
	int width = pixel % max_width;
	int height = 0;
	if (pixel == 0) {
		height = 0;
	}
	else {
		height = pixel / max_width;
	}
	int offset = (((height * max_width) * 2) + (width * 2));
	*y = (*((unsigned short*)(buffer + offset)))>>8;
	return;


}

void Cmm::getPbPixel(unsigned char *buffer, int pixel, short *pb, int max_width, int max_height)
{
	int pb_width = (pixel % max_width) / 2;
	int pb_height = 0;
	if (pixel == 0) {
		pb_height = 0;
	}
	else {
		pb_height = (pixel / max_width) / 2;
	}

	int pb_offset = getPbTopOffsetAddress(max_height, max_width);
	int offset = (((pb_height * (max_width / 2)) + pb_width) * 2);
	*pb = (*((unsigned short*)(buffer + pb_offset + offset)))>>8;
	return;
}
void Cmm::getPrPixel(unsigned char *buffer, int pixel, short *pr, int max_width, int max_height)
{
	int pr_width = (pixel % max_width) / 2;
	int pr_height = 0;
	if (pixel == 0) {
		pr_height = 0;
	}
	else {
		pr_height = (pixel / max_width) / 2;
	}
	int pr_offset = getPrTopOffsetAddress(max_width, max_height);
	int offset = ((pr_height * (max_width / 2) ) + pr_width) * 2;
	*pr = (*((unsigned short*)(buffer + pr_offset + offset)))>>8;
	return;
}

void Cmm::setYPixel(unsigned char y, int pixel, unsigned char *buf, int max_width, int max_heightf)
{
	int width = pixel % max_width;
	int height = 0;
	if (pixel == 0) {
		height = 0;
	}
	else {
		height = pixel / max_width;
	}

	*(buf + ((height * max_width) + width)) = y;

	return;
}
int Cmm::getPbTopOffsetAddress(int max_width, int max_height)
{
	return (max_height * max_width) * 2;
}

int Cmm::getPrTopOffsetAddress(int max_width, int max_height)
{
	return getPbTopOffsetAddress(max_height,max_width) + ((max_width / 2) * (max_height / 2) * 2);
}

