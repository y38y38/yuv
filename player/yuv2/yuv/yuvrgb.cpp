#include "stdafx.h"
#include "YuvRgb.h"

void YuvRgb::ypbpr2rgb(short y, short pb, short pr, unsigned char *rgb) {
	unsigned char *rgb_p = rgb;

	//€”õ
	double y_data = y;
	double pb_data = (pb - 128);
	double pr_data = (pr - 128);
	double temp_rgb;


	//b
	temp_rgb = (y_data + (1.8556 * pb_data));
	if (temp_rgb > 255) {
		temp_rgb = 255;
	}
	else if (temp_rgb < 0) {
		temp_rgb = 0;
	}
	*rgb_p = (unsigned char)temp_rgb;
	rgb_p++;
	//g
	temp_rgb = (y_data - (0.1873 * pb_data) - (0.4681 * pr_data));

	if (temp_rgb > 255) {
		temp_rgb = 255;
	}
	else if (temp_rgb < 0) {
		temp_rgb = 0;
	}
	*rgb_p = (unsigned char)temp_rgb;
	rgb_p++;

	//r
	temp_rgb = (y_data + (1.5748 * pr_data));
	if (temp_rgb > 255) {
		temp_rgb = 255;
	}
	else if (temp_rgb < 0) {
		temp_rgb = 0;
	}

	*rgb_p = (unsigned char)temp_rgb;
	rgb_p++;
}

