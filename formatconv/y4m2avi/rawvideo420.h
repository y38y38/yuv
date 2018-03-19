#ifndef _RAWVIDEO420_H_
#define _RAWVIDEO420_H_

void setBufferRawVideo420(int8_t *buffer);
void setParamRawVideo420(int32_t width, int32_t height);
size_t getFrameSizeRawVideo420(void);
int getBitNum(void);
void getPixelRawVideo420(int pixel, unsigned short *y, unsigned short *pb, unsigned short *pr);
void getYPixelRawVideo420(int pixel, unsigned short *y);
void setPixelRawVideo420(unsigned short y, unsigned short pb, unsigned short pr, int pixel);
void setYPixelRawVideo420(unsigned short y, int pixel);
#endif // _RAWVIDEO420_H_
