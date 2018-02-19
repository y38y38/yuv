#include <stdio.h>
#include "v210.h"

#define		BIT_NUM		(10)
#define		HORIZONTAL_ALIGN_PIXELS	(48)

static uint8_t *kBuffer;
static int32_t kWidth;
static int32_t kHeight;

void setBufferV210(int8_t *buffer)
{
    kBuffer = buffer;
}
void setParamV210(int32_t width, int32_t height)
{
    kWidth = width;
    kHeight = height;
}
unsigned char *getPixelBufferAddressv210(int pixel)
{
    unsigned char *buffer_address;
    
    if (((kWidth % HORIZONTAL_ALIGN_PIXELS) != 0)) {
        int file_width = ((HORIZONTAL_ALIGN_PIXELS - (kWidth % HORIZONTAL_ALIGN_PIXELS)) + kWidth);
        
        int current_height_position = pixel / kWidth;
        
        int line_top_address_offset_byte = (((file_width * current_height_position) / 6) * 16);
        
        int from_line_top_pixel = pixel - (current_height_position * kWidth);
        
        int from_line_top_pixel_offset_byte = ((from_line_top_pixel / 6) * 16);
        
        buffer_address = (kBuffer + line_top_address_offset_byte + from_line_top_pixel_offset_byte);
    
    } else {
        buffer_address = (kBuffer + (pixel / 6) * 16);
    
    }

return buffer_address;
}
void getPixelv210(int pixel, unsigned short *y, unsigned short *pb, unsigned short *pr)
{
	uint32_t *pic = (uint32_t*)getPixelBufferAddressv210(pixel);

	int offset_pixel = pixel % kWidth;

	if ((offset_pixel % 6 ) == 0) { 
		//Word 0
		*pb = (unsigned short)((*(pic)     & 0x000003ff) << 6);
		*y  = (unsigned short)((*(pic)     & 0x000ffc00) >> 4);
		*pr = (unsigned short)((*(pic)     & 0x3ff00000) >> 14);
	} else if ((offset_pixel % 6) == 1) {
		*pb = (unsigned short)((*(pic)     & 0x000003ff) << 6);
		*pr = (unsigned short)((*(pic)     & 0x3ff00000) >> 14);
		*y  = (unsigned short)((*(pic + 1) & 0x000003ff) << 6);
	} else if ((offset_pixel % 6) == 2) {
		*pb = (unsigned short)((*(pic + 1) & 0x000ffc00) >> 4);
		*y  = (unsigned short)((*(pic + 1) & 0x3ff00000) >> 14);
		*pr = (unsigned short)((*(pic + 2) & 0x000003ff) << 6);
	} else if ((offset_pixel % 6) == 3) {
		*pb = (unsigned short)((*(pic + 1) & 0x000ffc00) >> 4);
		*pr = (unsigned short)((*(pic + 2) & 0x000003ff) << 6);
		*y  = (unsigned short)((*(pic + 2) & 0x000ffc00) >> 4);
	} else if ((offset_pixel % 6) == 4) {
		*pb = (unsigned short)((*(pic + 2) & 0x3ff00000) >> 14);
		*y  = (unsigned short)((*(pic + 3) & 0x000003ff) << 6);
		*pr = (unsigned short)((*(pic + 3) & 0x000ffc00) >> 4);
	} else {//if ((pixel % 6) == 5) {
		*pb = (unsigned short)((*(pic + 2) & 0x3ff00000) >> 14);
		*pr = (unsigned short)((*(pic + 3) & 0x000ffc00) >> 4);
		*y  = (unsigned short)((*(pic + 3) & 0x3ff00000) >> 14);
	}
}

void setPixelv210(unsigned short y, unsigned short pb, unsigned short pr, int pixel)
{
	uint32_t *pic = (uint32_t*)getPixelBufferAddressv210(pixel);

        uint32_t shif;
        uint32_t oo;
	int offset_pixel = pixel % kWidth;
	if ((offset_pixel % 6 ) == 0) { 
		//Word 0
		*(pic)     = (*(pic    ) & ~0xc00003ff) | (((uint32_t )pb >> 6)  & 0x000003ff);
		*(pic)     = (*(pic    ) & ~0xc00ffc00) | (((uint32_t)y  << 4)  & 0x000ffc00);
       // shif = pr <<14;
        //oo = (*(pic    ) & ~0xfff00000);
		*(pic)     = (*(pic    ) & ~0xfff00000) | (((uint32_t)pr << 14) & 0x3ff00000);
        
	} else if ((offset_pixel % 6) == 1) {
		*(pic)     = (*(pic    ) & ~0xc00003ff) | (((uint32_t)pb >> 6)  & 0x000003ff);
		*(pic)     = (*(pic    ) & ~0xfff00000) | (((uint32_t)pr << 14) & 0x3ff00000);
		*(pic + 1) = (*(pic + 1) & ~0xc00003ff) | (((uint32_t)y  >> 6)  & 0x000003ff);
	} else if ((offset_pixel % 6) == 2) {
		*(pic + 1) = (*(pic + 1) & ~0xc00ffc00) | (((uint32_t)pb << 4)  & 0x000ffc00);
		*(pic + 1) = (*(pic + 1) & ~0xfff00000) | (((uint32_t)y  << 14) & 0x3ff00000);
		*(pic + 2) = (*(pic + 2) & ~0xc00003ff) | (((uint32_t)pr >> 6)  & 0x000003ff);
	} else if ((offset_pixel % 6) == 3) {
		*(pic + 1) = (*(pic + 1) & ~0xc00ffc00) | (((uint32_t)pb << 4)  & 0x000ffc00);
		*(pic + 2) = (*(pic + 2) & ~0xc00003ff) | (((uint32_t)pr >> 6)  & 0x000003ff);
		*(pic + 2) = (*(pic + 2) & ~0xc00ffc00) | (((uint32_t)y  << 4)  & 0x000ffc00);
	} else if ((offset_pixel % 6) == 4) {
		*(pic + 2) = (*(pic + 2) & ~0xfff00000) | (((uint32_t)pb << 14) & 0x3ff00000);
		*(pic + 3) = (*(pic + 3) & ~0xc00003ff) | (((uint32_t)y  >> 6)  & 0x000003ff);
		*(pic + 3) = (*(pic + 3) & ~0xc00ffc00) | (((uint32_t)pr << 4)  & 0x000ffc00);
	} else {//if ((pixel % 6) == 5) {
		*(pic + 2) = (*(pic + 2) & ~0xfff00000) | (((uint32_t)pb << 14) & 0x3ff00000);
		*(pic + 3) = (*(pic + 3) & ~0xc00ffc00) | (((uint32_t)pr << 4)  & 0x000ffc00);
		*(pic + 3) = (*(pic + 3) & ~0xfff00000) | (((uint32_t)y  << 14) & 0x3ff00000);
	}
}

void setYPixelv210(unsigned short y, int pixel)
{
	uint32_t *pic = (uint32_t*)getPixelBufferAddressv210(pixel);

	int offset_pixel = pixel % kWidth;

	if ((offset_pixel % 6 ) == 0) {
		//Word 0
		*(pic    ) = (*(pic    ) & ~0xc00ffc00) | (((uint32_t)y << 4)  & 0x000ffc00);
	} else if ((offset_pixel % 6) == 1) {
		*(pic + 1) = (*(pic + 1) & ~0xc00003ff) | (((uint32_t)y >> 6)  & 0x000003ff);

	} else if ((offset_pixel % 6) == 2) {
		*(pic + 1) = (*(pic + 1) & ~0xfff00000) | (((uint32_t)y << 14) & 0x3ff00000);
	} else if ((offset_pixel % 6) == 3) {
		*(pic + 2) = (*(pic + 2) & ~0xc00ffc00) | (((uint32_t)y << 4)  & 0x000ffc00);
	} else if ((offset_pixel % 6) == 4) {
		*(pic + 3) = (*(pic + 3) & ~0xc00003ff) | (((uint32_t)y >> 6)  & 0x000003ff);
	} else {//if ((pixel % 6) == 5) {
		*(pic + 3) = (*(pic + 3) & ~0xfff00000) | (((uint32_t)y << 14) & 0x3ff00000);
	}
	return;
}
