#ifndef _CMM422_H_
#define _CMM422_H_

int cmm422GetFrameSize(int width, int height);

void cmm422GetYPixel(unsigned short *buffer, int pixel, unsigned short *y, int max_width, int  max_height); 

void cmm422GetCbPixel(unsigned short *buffer, int pixel, unsigned short *cb, int max_width, int  max_height);

void cmm422GetCrPixel(unsigned short *buffer, int pixel, unsigned short *cr, int max_width, int  max_height);


void cmm422SetYPixel(unsigned short *buffer, int pixel, unsigned short y, int max_width, int  max_height); 

void cmm422SetCbPixel(unsigned short *buffer, int pixel, unsigned short cb, int max_width, int  max_height);

void cmm422SetCrPixel(unsigned short *buffer, int pixel, unsigned short cr, int max_width, int  max_height);

#endif //_CMM_H_
