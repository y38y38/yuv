#ifndef _CMM2YUV4_H_
#define _CMM2YUV4_H_

int cmm2cmm(unsigned char* input, unsigned char *output,int input_width,  int input_height, int output_width, int output_height);
int inputFrameSize(int width, int height);
int outputFrameSize(int width, int height);

#endif //_CMM2YUV4_H_
