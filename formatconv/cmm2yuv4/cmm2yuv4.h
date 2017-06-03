#ifndef _CMM2YUV4_H_
#define _CMM2YUV4_H_

int cmm2yuv4(unsigned char* input, unsigned char *output, int height, int width);
int inputFrameSize(int width, int height);
int outputFrameSize(int width, int height);

#endif //_CMM2YUV4_H_
