#include "stdio.h"
#include "stdbool.h"
#include "yuv4.h"
#include "cmm.h"

#include "cmm2yuv4.h"

int inputFrameSize(int width, int height) {
    return cmmGetFrameSize(width, height);
}

int outputFrameSize(int width, int height) {
    return yuv4GetFrameSize(width, height);
}

int cmm2yuv4(unsigned char* input, unsigned char *output, int height, int width)
{
    int i;
    int j;
    unsigned short  value;
    unsigned short *output_short = (unsigned short*)output;

    //y
    for(i = 0;i < height;i++) {
        for(j = 0;j < width;j++) {

            cmmGetYPixel((unsigned short*)input, ((i * width) + j), &value, width, height);
            unsigned char y_char = (unsigned char)(((unsigned short)value) >> 8);
            yuv4SetYPixel(output, ((i *width) + j), y_char, width, height);
        }
    }
    int c_width = width / 2;
    int c_height = height / 2;
    
    //cb
	char cb_value;
    for(i = 0;i < c_height;i++) {
        for(j = 0;j < c_width;j++) {

            cmmGetCbPixel((unsigned short*)input, ((i * c_width) + j), &value, c_width, c_height);
            char cb_char = (char)((value) >> 8);
			cb_char -= 128;
            yuv4SetCbPixel(output, ((i * c_width) + j), cb_char, c_width, c_height);
        }
    }
    //cr
    for(i = 0;i < c_height;i++) {
        for(j = 0;j < c_width;j++) {

            cmmGetCrPixel((unsigned short*)input, ((i * c_width) + j), &value, c_width, c_height);
            char cr_char = (char)(((unsigned short)value) >> 8);
			cr_char -= 128;
            yuv4SetCrPixel(output, ((i * c_width) + j), cr_char, c_width , c_height );
        }
    }
    return 0;
}

