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
    for(i = 0;i < height/2;i++) {
        for(j = 0;j < width/2;j++) {

            yuv4GetCbPixel(input, ((i * width) + j), &value, width, height);
            unsigned short cb_short = (unsigned short)(((unsigned short)value) << 8);
            *(output_short + (height * width) + ((i * (width/2)) + j)) =  cb_short;
        }
    }
    //cr
    for(i = 0;i < height/2;i++) {
        for(j = 0;j < width/2;j++) {

            yuv4GetCrPixel(input, ((i * width) + j), &value, width, height);
            unsigned short cr_short = (unsigned short)(((unsigned short)value) << 8);
            *(output_short + (height * width) + ((height/2) * (width/2)) + ((i * (width/2)) + j)) =  cr_short;
        }
    }
    return 0;
}

