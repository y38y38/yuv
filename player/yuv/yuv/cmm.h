#pragma once

class Cmm {
public:
	Cmm(void) { return; }
	~Cmm(void) { return; }
	static int getRgb(unsigned char *ypbpr_buffer, int width, int height, unsigned char *output_rgb_buffer, BOOL enable_y, BOOL enable_pb, BOOL enable_pr);
	static int getFrameBufferSize(int width, int height);
	static void getPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr, int max_width, int max_height);
	static void getYPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr, int max_width, int max_height);
	static void setYPixel(unsigned char y, int pixel, unsigned char *buf, int max_width, int max_height);

private:
	static void getPbPixel(unsigned char *buffer, int pixel, short *pb, int max_width, int max_height);
	static void getPrPixel(unsigned char *buffer, int pixel, short *pr, int max_width, int max_height);
	static int getPbTopOffsetAddress(int max_width, int max_height);
	static int getPrTopOffsetAddress(int max_width, int max_height);
};
