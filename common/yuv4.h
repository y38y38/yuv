#ifndef _YUV4_H_
#define _YUV4_H_

int yuv4GetFrameSize(int width, int height);

void yuv4GetYPixel(unsigned char *buffer, int pixel, unsigned char *y, int max_width, int  max_height); 

void yuv4GetCbPixel(unsigned char *buffer, int pixel, char *cb, int max_width, int  max_height);

void yuv4GetCrPixel(unsigned char *buffer, int pixel, char *cr, int max_width, int  max_height);

void yuv4SetYPixel(unsigned char *buffer, int pixel, unsigned char y, int max_width, int  max_height); 

//cb -127,127
void yuv4SetCbPixel(unsigned char *buffer, int pixel, char cb, int max_width, int  max_height);
//cr -127,127
void yuv4SetCrPixel(unsigned char *buffer, int pixel, char cr, int max_width, int  max_height);

#endif //_YUV4_H_
