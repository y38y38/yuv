#include <stdio.h>
#include "rawvideo420.h"

static uint8_t *kBuffer;
static int32_t kWidth;
static int32_t kHeight;
void setBufferRawVideo420(int8_t *buffer)
{
    kBuffer = buffer;
}
void setParamRawVideo420(int32_t width, int32_t height)
{
    kWidth = width;
    kHeight = height;
}

size_t getFrameSizeRawVideo420(void)
{
	return ((kWidth * kHeight ) + ((kWidth * kHeight) / 2));
}

int getBitNum(void)
{
	return 8;
}


void getPixelRawVideo420(int pixel, unsigned short *y, unsigned short *pb, unsigned short *pr)
{
	*y = *(kBuffer + pixel);
	*y <<= 8;
	*y &= 0xff00;

	int line_num = pixel / kWidth;

	*pb = *(kBuffer + (kWidth * kHeight) + (pixel / 4));

	*pb = *(kBuffer + (kWidth * kHeight) + (((pixel / kWidth) / 2) * kWidth) + (pixel % kWidth));

	if ((line_num % 2) == 0) {
		*pb = *(kBuffer + (kWidth * kHeight) + (((pixel / kWidth) / 4) * kWidth) + ((pixel % kWidth) / 2));
	} else {
		*pb = *(kBuffer + (kWidth * kHeight) + (((pixel / kWidth) / 4) * kWidth) + (kWidth / 2 ) + ((pixel % kWidth) / 2));
	}

	*pb <<= 8;
	*pb &= 0xff00;

	*pr = *(kBuffer + (kWidth * kHeight) + ((kWidth * kHeight) / 4) + (pixel / 4));
	if ((line_num % 2) == 0) {
		*pr = *(kBuffer + (kWidth * kHeight) + ((kWidth * kHeight) / 4)+(((pixel / kWidth) / 4) * kWidth) + ((pixel % kWidth) / 2));
	} else {
		*pr = *(kBuffer + (kWidth * kHeight) + ((kWidth * kHeight) / 4)+ (((pixel / kWidth) / 4) * kWidth) + (kWidth / 2 ) + ((pixel % kWidth) / 2));
	}
	*pr <<= 8;
	*pr &= 0xff00;

}


void getYPixelRawVideo420(int pixel, unsigned short *y)
{
	*y = *(kBuffer + pixel);
	*y <<= 8;
	*y &= 0xff00;
}

void setPixelRawVideo420(unsigned short y, unsigned short pb, unsigned short pr, int pixel)
{
	*(kBuffer + pixel) = (unsigned char)(y>>8);
	*(kBuffer + (kWidth * kHeight) + (pixel / 4)) = (unsigned char)(pb>>8);
	*(kBuffer + (kWidth * kHeight) + ((kWidth * kHeight) / 4) + (pixel / 4)) = (unsigned char)(pr>>8);
}

void setYPixelRawVideo420(unsigned short y, int pixel)
{
	*(kBuffer + pixel) = (unsigned char)(y>>8);

}


