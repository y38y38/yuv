#include "stdio.h"
#include "stdbool.h"
#include "yuv4.h"

int yuv42cmm(unsigned char* input, unsigned char *output, int height, int width)
{
    int i;
    int j;
    unsigned char value;
    unsigned short *output_short = (unsigned short*)output;

    //y
    for(i = 0;i < height;i++) {
        for(j = 0;j < width;j++) {

            yuv4GetYPixel(input, ((i * width) + j), &value, width, height);
            unsigned short y_short = (unsigned short)(((unsigned short)value) << 8);
            *(output_short + ((i * width) + j)) =  y_short;
        }
    }
    //cb
    char cb_value;
	unsigned short cb_short;
    for(i = 0;i < height/2;i++) {
        for(j = 0;j < width/2;j++) {

            yuv4GetCbPixel(input, ((i * (width/2)) + j), &cb_value, width/2, height/2);
			cb_short = (unsigned short)(cb_value + 128);
			cb_short <<= 8;
            *(output_short + (height * width) + ((i * (width/2)) + j)) =  cb_short;
        }
    }
    //cr
    char cr_value;
	unsigned short cr_short;
    for(i = 0;i < height/2;i++) {
        for(j = 0;j < width/2;j++) {

            yuv4GetCrPixel(input, ((i * (width/2)) + j), &cr_value, width/2, height/2);
			cr_short = (unsigned short)(cr_value + 128);
			cr_short <<= 8;
            *(output_short + (height * width) + ((height/2) * (width/2)) + ((i * (width/2)) + j)) =  cr_short;
        }
    }
    return 0;
}

