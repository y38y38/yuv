#include "stdio.h"

#include "cmm422.h"

int cmm422GetFrameSize(int width, int height)
{
	if (width == 0) return 0;
	if (height == 0) return 0;

	return (((width * height) * 2) + (((width / 2) * (height))  * 4));
}
void cmm422GetYPixel(unsigned short *buffer, int pixel, unsigned short *y, int max_width, int  max_height) {
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

void cmm422GetCbPixel(unsigned short *buffer, int pixel, unsigned short *cb, int max_width, int  max_height) {
	//pointer is short
	
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }

    *cb = *(buffer + ((max_height) * (max_width * 2)) + ((height * (max_width)) + width));
}

void cmm422GetCrPixel(unsigned short *buffer, int pixel, unsigned short *cr, int max_width, int  max_height) {
	//pointer is short
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }
	int offset =  ((max_height) * (max_width * 2)) + (max_height * max_width ) + ((height * max_width) + width);
    *cr = *(buffer + offset);
    unsigned short tmp  = *(buffer + offset);
	*cr = tmp;
    //*cr = *(buffer + ((max_height * 2) * (max_width * 2)) + (max_height * max_width ) + ((height * max_width) + width));
}

void cmm422SetYPixel(unsigned short *buffer, int pixel, unsigned short y, int max_width, int  max_height) {
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

void cmm422SetCbPixel(unsigned short *buffer, int pixel, unsigned short cb, int max_width, int  max_height) {
	//pointer is short
	
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }

    *(buffer + ((max_height) * (max_width * 2)) + ((height * (max_width)) + width)) = cb;
}

void cmm422SetCrPixel(unsigned short *buffer, int pixel, unsigned short cr, int max_width, int  max_height) {
	//pointer is short
    int width = pixel % max_width;
    int height= 0;
    if (pixel == 0) {
        height = 0;
    } else {
        height = pixel / max_width;
    }
	int offset =  ((max_height) * (max_width * 2)) + (max_height * max_width ) + ((height * max_width) + width);
    *(buffer + offset) = cr;
//    unsigned short tmp  = *(buffer + offset);
//	tmp = cr;
    //*cr = *(buffer + ((max_height * 2) * (max_width * 2)) + (max_height * max_width ) + ((height * max_width) + width));
}
