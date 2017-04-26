#pragma once

class Yuv4 {
public:
	Yuv4(void) { return; }
	~Yuv4(void) { return; }
	static int getRgb(unsigned char *ypbpr_buffer, int width, int height, unsigned char *output_rgb_buffer, BOOL enable_y, BOOL enable_pb, BOOL enable_pr);
	static int getFrameBufferSize(int width, int height);
	static void getPixel(unsigned char *buffer, int pixel, short *y, short *pb, short *pr, int width, int height);

private:

};
