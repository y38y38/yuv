#include "stdio.h"

#include "cmm.h"

int cmmGetFrameSize(int width, int height)
{
	if (width == 0) return 0;
	if (height == 0) return 0;

	return (((width * height) * 2) + (((width * height) / 2) * 2));
}
void cmmGetYPixel(unsigned short *buffer, int pixel, unsigned short *y, int max_width, int  max_height) {
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }

    *y = *(buffer + (( height * max_width) + width));
    return;
}

void cmmGetCbPixel(unsigned short *buffer, int pixel, unsigned short *cb, int max_width, int  max_height) {
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }

    *cb = *(buffer + (height * width) + ((height * (max_width/2)) + width));
}

void cmmGetCrPixel(unsigned short *buffer, int pixel, unsigned short *cr, int max_width, int  max_height) {
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }
    *cr = *(buffer + (max_height * max_width) + ((max_height / 2) * (max_width / 2)) + ((height * (max_width/2)) + width));
}
