#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "cmm.h"

double sn(unsigned short *data1, unsigned short *data2, int num, int bit_num)
{
	double sn_sum;
	
	sn_sum = 0;
	for (int i = 0;i < num; i++) {

		unsigned short temp1 = *(data1 + i);
		unsigned short temp2 = *(data2 + i);
		temp1 = temp1 >> (16 - bit_num);
		temp2 = temp2 >> (16 - bit_num);

		int a,b;
		a = (int)temp1;
		b = (int)temp2;

		int diff;
		diff = a;
		diff -= b;
		
		int x2 = diff * diff;

		sn_sum += x2;

	}
	double rmse = sn_sum / num;
	rmse = sqrt(rmse);

	int max = ((1 << bit_num) - 1);

	double psnr = (rmse != 0) ? -20 * log10(rmse/max) : 120;

	return psnr;
}
int getbuffer(int height, int width, unsigned short **y, unsigned short **cb, unsigned short **cr)
{
	*y = (unsigned short *)malloc(height*width*2);
	if (*y == NULL) {
		printf("malloc ng\n");
		return -1;
	}
	*cb = (unsigned short *)malloc((height*width)/2);
	//printf("0x%x %d\n", *cb, (height*width)/2);
	if (*cb == NULL) {
		printf("malloc ng\n");
		return -1;
	}
	*cr = (unsigned short *)malloc((height*width)/2);
	//printf("0x%x %d\n", *cr, (height*width)/2);
	if (*cr == NULL) {
		printf("malloc ng\n");
		return -1;
	}
	return 0;
}


int sn_calc(unsigned short *y1, unsigned short *y2, unsigned short *cb1, unsigned short *cb2, unsigned short *cr1, unsigned short *cr2, int height, int width)
{
	double psnr = sn(y1, y2, height * width, 8);
	printf("y,%f,", psnr);
	psnr = sn(cb1, cb2, height * width / 4, 8);
	printf("cb,%f,", psnr);
	psnr = sn(cr1, cr2, height * width / 4, 8);
	printf("cr,%f\n", psnr);
	return 0;
}

int getsignal(unsigned char *frame, int height, int width, unsigned short **y, unsigned short **cb, unsigned short **cr)
{
	int ret = getbuffer(height, width, y, cb, cr);
	if (ret < 0) {
		printf("getbuffer ng\n");
		return -1;
	}
	//y
	for (int pixel = 0;pixel < height * width;pixel++) {
		cmmGetYPixel((unsigned short*)frame, pixel,*y + pixel, width, height);
	}

	//cb
	for (int pixel = 0;pixel < (height * width) / 4;pixel++) {
		cmmGetCbPixel((unsigned short*)frame, pixel,*cb + pixel, width/2, height/2);
	}

	//cr
	for (int pixel = 0;pixel < (height * width) / 4;pixel++) {
		cmmGetCrPixel((unsigned short*)frame, pixel,*cr + pixel, width/2, height/2);
	}

	return 0;
}

int sn_frame(unsigned char* frame1, unsigned char *frame2, int height, int width)
{
	unsigned short *y1, *y2, *cb1, *cb2, *cr1, *cr2;
	int ret = getsignal(frame1, height, width, &y1, &cb1, &cr1);
	if (ret < 0) {
		printf("getsignal ng\n");
		return -1;
	}
	ret = getsignal(frame2, height, width, &y2, &cb2, &cr2);
	if (ret < 0) {
		printf("getsignal ng\n");
		return -1;
	}


	ret = sn_calc(y1, y2, cb1, cb2, cr1,cr2,height, width);
	if (ret < 0) {
		printf("sn_calc ng\n");
		return -1;
	}

	return 0;
}

int inputFrameSize(int width, int height) {
    return cmmGetFrameSize(width, height);
}

int outputFrameSize(int width, int height) {
    return cmmGetFrameSize(width, height);
}

int sn_file(FILE *input1, FILE *input2, int width, int height)
{

	void *inbuf1;
	void *inbuf2;
    int i;

	int input_framesize = inputFrameSize(width, height);
	inbuf1 = malloc(input_framesize);
	printf("i %d\n", input_framesize);

	if (inbuf1 == NULL) {
		printf("err malloc 1\n");
		return -1;
	}
	inbuf2 = malloc(input_framesize);

	if (inbuf2 == NULL) {
		printf("err malloc 1\n");
		return -1;
	}

	for (i=0;;i++) {

		size_t readsize = fread(inbuf1, 1, input_framesize, input1);
        if (readsize == 0 ) {
            printf("OK end of file %d \n", i);
            return 0;
        } else if (readsize != input_framesize) {
            printf("fread err\n");
			return -1;
		} else {
		}
		readsize = fread(inbuf2, 1, input_framesize, input2);
        if (readsize == 0 ) {
            printf("NG end of file %d\n", i);
            return 0;
        } else if (readsize != input_framesize) {
            printf("fread err\n");
			return -1;
		} else {
		}

		int ret = sn_frame(inbuf1, inbuf2, height, width);
		if (ret < 0) {
			printf("frame ng\n");
		}

	}
	return 0;

}



//parameter1 input 1
//parameter2 input 2
//parameter3 height
//parameter4 width

//format cmm only
int main(int argc, char** argv)
{
	if (argc != 5) {
		printf("sn.exe input_filename input_filename height width\n");
		return -1;
	}
	FILE *input1 = fopen((const char*)argv[1], "r");
	if (input1 == NULL) {
		printf("can't open file\n");
		return -1;
	}

	FILE *input2 = fopen((const char*)argv[2], "r");
	if (input2 == NULL) {
		printf("can't open file\n");
		return -1;
	}

	int width = atoi((const char*)argv[3]);
	int height = atoi((const char*)argv[4]);

	int ret = sn_file(input1, input2, width, height);
	if (ret < 0) {
		printf("ng\n");
	}

	fclose(input1);
	fclose(input2);
	
	return 0;
}

