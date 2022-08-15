#ifndef _CMM_H_
#define _CMM_H_

int cmmGetFrameSize(int width, int height);

void cmmGetYPixel(unsigned short *buffer, int pixel, unsigned short *y, int max_width, int  max_height); 

void cmmGetCbPixel(unsigned short *buffer, int pixel, unsigned short *cb, int max_width, int  max_height);

void cmmGetCrPixel(unsigned short *buffer, int pixel, unsigned short *cr, int max_width, int  max_height);


void cmmSetYPixel(unsigned short *buffer, int pixel, unsigned short y, int max_width, int  max_height); 

void cmmSetCbPixel(unsigned short *buffer, int pixel, unsigned short cb, int max_width, int  max_height);

void cmmSetCrPixel(unsigned short *buffer, int pixel, unsigned short cr, int max_width, int  max_height);

#endif //_CMM_H_
