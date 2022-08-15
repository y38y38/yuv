#include "stdio.h"

#include "cmm.h"

int cmmGetFrameSize(int width, int height)
{
	if (width == 0) return 0;
	if (height == 0) return 0;

	return (((width * height) * 2) + (((width / 2) * (height / 2))  * 4));
}
void cmmGetYPixel(unsigned short *buffer, int pixel, unsigned short *y, int max_width, int  max_height) {
	//pointer is short
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
	//pointer is short
	
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }

    *cb = *(buffer + ((max_height * 2) * (max_width * 2)) + ((height * (max_width)) + width));
}

void cmmGetCrPixel(unsigned short *buffer, int pixel, unsigned short *cr, int max_width, int  max_height) {
	//pointer is short
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }
	int offset =  ((max_height * 2) * (max_width * 2)) + (max_height * max_width ) + ((height * max_width) + width);
    *cr = *(buffer + offset);
    unsigned short tmp  = *(buffer + offset);
	*cr = tmp;
    //*cr = *(buffer + ((max_height * 2) * (max_width * 2)) + (max_height * max_width ) + ((height * max_width) + width));
}

void cmmSetYPixel(unsigned short *buffer, int pixel, unsigned short y, int max_width, int  max_height) {
	//pointer is short
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }

    *(buffer + (( height * max_width) + width)) = y;
    return;
}

void cmmSetCbPixel(unsigned short *buffer, int pixel, unsigned short cb, int max_width, int  max_height) {
	//pointer is short
	
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }

    *(buffer + ((max_height * 2) * (max_width * 2)) + ((height * (max_width)) + width)) = cb;
}

void cmmSetCrPixel(unsigned short *buffer, int pixel, unsigned short cr, int max_width, int  max_height) {
	//pointer is short
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }
	int offset =  ((max_height * 2) * (max_width * 2)) + (max_height * max_width ) + ((height * max_width) + width);
    *(buffer + offset) = cr;
//    unsigned short tmp  = *(buffer + offset);
//	tmp = cr;
    //*cr = *(buffer + ((max_height * 2) * (max_width * 2)) + (max_height * max_width ) + ((height * max_width) + width));
}
