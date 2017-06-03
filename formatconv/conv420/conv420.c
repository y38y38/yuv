#include "conv420.h"

int conv(unsigned char* input, unsigned char *output, int height, int width)
{
    int i;
    int j;
    unsigned char value;
    unsigned short *output_short = (unsigned short*)output;
    for(i = 0;i < height;i++) {
        for(j = 0;j < width;j++) {
            value = *(input + ((width * i) + j));
            unsigned short y_short = (unsigned short)(((unsigned short)value) << 8);
            *(output_short + ((i * width) + j)) =  y_short;
        }
    }
    return 0;
}

int conv420(unsigned char* input, unsigned char *output, int height, int width)
{
    int ret = conv(input, output, height, width);
    if (ret < 0) {
        return -1;
    }

    input = input + (height * width); 
    output = output + ((height * width) * 2);
    ret = conv(input, output, height, width);
    if (ret < 0) {
        return -1;
    }

    input = input + ((height * width) / 4); 
    output = output + (((height * width) * 2) / 4);
    ret = conv(input, output, height, width);
    if (ret < 0) {
        return -1;
    }
    return 0;
}
