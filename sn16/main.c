#include "stdio.h"
#include "stdlib.h"
#include "math.h"


void GetYPixel(unsigned short* buffer, int pixel, unsigned short *y, int width, int height)
{
    if (width == 0) {
        *y = 0x200;
        return;
    }
    if (height == 0) {
        *y = 0x200;
        return;
    }
    *y = *(buffer + (pixel % width) + ((pixel / width) * width));

}
void GetCbPixel(unsigned short* buffer, int pixel, unsigned short *cb, int width, int height)
{
    if (width == 0) {
        *cb = 0x200;
        return;
    }
    if (height == 0) {
        *cb = 0x200;
        return;
    }
    *cb = *(buffer + (width * height) + (pixel % (width / 2)) + ((pixel / (width / 2)) * (width / 2)));

}
void GetCrPixel(unsigned short* buffer, int pixel, unsigned short *cr, int width, int height)
{
    if (width == 0) {
        *cr = 0x200;
        return;
    }
    if (height == 0) {
        *cr = 0x200;
        return;
    }
    *cr = *(buffer + (width * height) + ((width / 2) * height) + (pixel % (width / 2)) + ((pixel / (width / 2)) * (width / 2)));

}
int abs22(int val)
{
    if (val < 0) {
        //printf("m\n");
        return val * -1;
    } else {
        //printf("p\n");
        return val;
    }
}
int max(int a, int b)
{
    if( a > b) {
        return a;
    } else {
        return b;
    }
}
double sn(unsigned short *data1, unsigned short *data2, int num, int bit_num, int * max_diff)
{
	double sn_sum;
	*max_diff = 0;
	sn_sum = 0;
	for (int i = 0;i < num; i++) {

		unsigned short temp1 = *(data1 + i);
		unsigned short temp2 = *(data2 + i);
		//temp1 = temp1 >> (16 - bit_num);
		//temp2 = temp2 >> (16 - bit_num);
        //printf("%d %d\n",temp1, temp2);

		int a,b;
		a = (int)temp1;
		b = (int)temp2;

		int diff;
		diff = a;
		diff -= b;

        int abs = abs22(diff);
        *max_diff = max(*max_diff, abs);
		
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
    int max_diff;
	double psnr = sn(y1, y2, height * width, 10, &max_diff);
	printf("y,%f, max diff,%d,", psnr,max_diff);
	psnr = sn(cb1, cb2, height * width / 4, 10, &max_diff);
	printf("cb,%f, max diff,%d,", psnr,max_diff);
	psnr = sn(cr1, cr2, height * width / 4, 10, &max_diff);
	printf("cr,%f, max diff,%d\n", psnr,max_diff);
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
		GetYPixel((unsigned short*)frame, pixel,*y + pixel, width, height);
	}

	//cb
	for (int pixel = 0;pixel < (height * width) / 4;pixel++) {
		GetCbPixel((unsigned short*)frame, pixel,*cb + pixel, width/2, height/2);
	}

	//cr
	for (int pixel = 0;pixel < (height * width) / 4;pixel++) {
		GetCrPixel((unsigned short*)frame, pixel,*cr + pixel, width/2, height/2);
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
int GetFrameSize(int width, int height)
{
    return ((width * height) + (width * height)) * 2;
}
int inputFrameSize(int width, int height) {
    return GetFrameSize(width, height);
}

int outputFrameSize(int width, int height) {
    return GetFrameSize(width, height);
}

int sn_file(FILE *input1, FILE *input2, int width, int height)
{

	void *inbuf1;
	void *inbuf2;
    int i;

	int input_framesize = inputFrameSize(width, height);
	inbuf1 = malloc(input_framesize);
	//printf("i %d\n", input_framesize);

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
            //printf("OK end of file %d \n", i);
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

