#include "stdafx.h"

#include "YuvRgb.h"

#include "Yuv4.h"


int Yuv4::getFrameBufferSize(int width, int height)
{
	if (width == 0) return 0; //0èúéZëŒçÙ
	if (height == 0) return 0;//0èúéZëŒçÙ

	return ((width * height) + ((width * height) / 2));

}

int Yuv4::getRgb(unsigned char *ypbpr_buffer, int width, int height, unsigned char *output_rgb_buffer, BOOL enable_y, BOOL enable_pb, BOOL enable_pr)
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
		YuvRgb *yuvrgbp = new YuvRgb();
		yuvrgbp->ypbpr2rgb(y, pb, pr, rgb_buffer);
		rgb_buffer += 3;
	}
	return 0;
}
void Yuv4::getPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr, int max_width, int  max_height) {
//CbCbY1Y1Y2Y2CrCr


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


	*y = *(buffer + height_offset + width + y_offset_cbcr + y_offset_y);


	//*pb = *(buffer + (max_width * max_height) + ((width / 2) + ((height / 2) * (max_width / 2))));
	//*pr = *(buffer + (max_width * max_height) + ((max_width / 2) * (max_height / 2)) + ((width / 2) + ((height / 2) * (max_width / 2))));
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
	short pb_value, pr_value;
	pb_value = *(buffer + height_offset + cb_offset_y + cb_offset_cr + (width /2));
	*pb = (pb_value + 128) & 0xff;

	pr_value = *(buffer + height_offset + cb_offset_y + cb_offset_cr + (width / 2) + 1);
	*pr = (pr_value + 128) & 0xff;
	return;
}
