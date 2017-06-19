#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include "yuv4.h"


int yuv4GetFrameSize(int width, int height)
{
	if (width == 0) return 0; //0èúéZëŒçÙ
	if (height == 0) return 0;//0èúéZëŒçÙ

	return ((width * height) + ((width * height) / 2));

}
static int Yuv4GetYOffset(int pixel, int max_width, int  max_height)
{
	int height;
	int width = pixel % max_width;
	if(pixel == 0) {
		height = 0;
	}
	else {
		height = pixel / max_width;
	}

	

	int y_offset_cbcr = 0;
	if (width == 0) {
		y_offset_cbcr = 2;
	}
	else {
		y_offset_cbcr = (((width / 2) * 2) + 2);
	}

	int y_offset_y = 0;
	if ((height % 2) == 0) {
		y_offset_y = (((width / 2) * 2));
	} else {
		y_offset_y = (((width / 2) * 2) + 2);
	}
	int height_offset;

	if (height == 0) {
		height_offset = 0;
	} else {
		height_offset = (height / 2) * (max_width * 3);

	}


	return height_offset + width + y_offset_cbcr + y_offset_y;
}
void yuv4GetYPixel(unsigned char *buffer, int pixel, unsigned char *y, int max_width, int  max_height) {
//CbCrY1Y1Y2Y2CbCr

    *y = *(buffer + Yuv4GetYOffset(pixel, max_width, max_height));

    return;
}
static int Yuv4GetCbOffset(int pixel, int max_width, int  max_height)
{
//printf("%d %d %d\n", pixel, max_width, max_height);
    int tmp_width,tmp_height;
    tmp_width = pixel % max_width;
    if (pixel == 0) {
        tmp_height = 0; 
    } else {
        tmp_height = pixel / max_width;
    }
    tmp_width = tmp_width * 2;
    tmp_height = tmp_height * 2;



    pixel = ((max_width * 2) * tmp_height) + tmp_width;
    max_width = max_width * 2;
    max_height = max_height * 2;

	int height;
	int width = pixel % max_width;
	if(pixel == 0) {
		height = 0;
	}
	else {
		height = pixel / max_width;
	}

	int height_offset;

	if (height == 0) {
		height_offset = 0;
	} else {
		height_offset = (height / 2) * (max_width * 3);

	}



	int cbcr_offset;
	if (pixel == 0) {
		cbcr_offset = 0;
	}
	else {
		cbcr_offset = ((pixel) / 4);
	}

	int cb_offset_y;
	if (width == 0) {
		cb_offset_y = 0;
	}
	else {
		cb_offset_y = (((width / 2) * 2)) * 2;
	}

	int cb_offset_cr;
	if (width == 0) {
		cb_offset_cr = 0;
	}
	else {
		cb_offset_cr = width / 2;
	}



	if (width == 0) {
		width = 1;
	}
	//printf("offset,%d\n", (height_offset + cb_offset_y + cb_offset_cr + (width /2)));
	return (height_offset + cb_offset_y + cb_offset_cr + (width /2));

}
void yuv4GetCbPixel(unsigned char *buffer, int pixel, char *cb, int max_width, int  max_height) {
//CbCrY1Y1Y2Y2CbCr

	char cb_value;
	cb_value = *(buffer + Yuv4GetCbOffset(pixel , max_width, max_height));
	*cb = cb_value;

	return;
}
static int Yuv4GetCrOffset(int pixel, int max_width, int  max_height)
{
#if 0
    pixel = pixel * 4;
    max_width = max_width * 2;
    max_height = max_height * 2;

	int height;
	int width = pixel % max_width;
	if(pixel == 0) {
		height = 0;
	}
	else {
		height = pixel / max_width;
	}

	int height_offset;

	if (height == 0) {
		height_offset = 0;
	} else {
		height_offset = (height / 2) * (max_width * 3);

	}



	int crcr_offset;
	if (pixel == 0) {
		crcr_offset = 0;
	}
	else {
		crcr_offset = ((pixel) / 4);
	}

	int cr_offset_y;
	if (width == 0) {
		cr_offset_y = 0;
	}
	else {
		cr_offset_y = (((width / 2) * 2)) * 2;
	}

	int cr_offset_cr;
	if (width == 0) {
		cr_offset_cr = 0;
	}
	else {
		cr_offset_cr = width / 2;
	}

	if (width == 0) {
		width = 1;
	}
	return (height_offset + cr_offset_y + cr_offset_cr + (width / 2) + 1);
#else

	return (pixel * 6) + 1;

#endif

}
void yuv4GetCrPixel(unsigned char *buffer, int pixel, char *cr, int max_width, int  max_height) {
//CbCrY1Y1Y2Y2CbCr

	char cr_value;

	cr_value = *(buffer + Yuv4GetCrOffset(pixel, max_width, max_height));
	*cr = cr_value;
	return;
}

void yuv4SetYPixel(unsigned char *buffer, int pixel, unsigned char y, int max_width, int  max_height) {
	*(buffer + Yuv4GetYOffset(pixel, max_width, max_height)) = y;
}

void yuv4SetCbPixel(unsigned char *buffer, int pixel, char cb, int max_width, int  max_height) {
	*(buffer + Yuv4GetCbOffset(pixel, max_width, max_height)) = (unsigned char)cb;

}

void yuv4SetCrPixel(unsigned char *buffer, int pixel, char cr, int max_width, int  max_height) {
	*(buffer + Yuv4GetCrOffset(pixel, max_width, max_height)) = (unsigned char)cr;

}
