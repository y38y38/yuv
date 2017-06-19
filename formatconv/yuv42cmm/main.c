#include  <stdio.h>
#include  <stdlib.h>

#include "yuv42cmm.h"



int conv_frame(unsigned char *input, unsigned char *output, int height, int width)
{
	return yuv42cmm(input, output, height, width);
}

int conv_file(FILE *input, FILE *output, int width, int height)
{

	void *inbuf;
	void *outbuf;
    int i;

	int input_framesize = (width * height)  +  ((width * height) / 2); //4:2:0 and 8bit
	inbuf = malloc(input_framesize);
	if (inbuf == NULL) {
		printf("err malloc 1\n");
		return -1;
	}

	int output_framesize = ((width *height) * 2) +  (((width * height) / 2) * 2); //4:2:0 and 2byte @ component
	outbuf = malloc(output_framesize);
	if (outbuf == NULL) {
		printf("err malloc 2\n");
		return -1;
	}
	//printf("size = %d,%d\n",input_framesize, output_framesize);
	for (i=0;;i++) {

		size_t readsize = fread(inbuf, 1, input_framesize, input);
        if (readsize == 0 ) {
            printf("OK end of file %d\n", i);
            return 0;
        } else if (readsize != input_framesize) {
            printf("fread err\n");
			return -1;
		} else {
		}

		//printf("start %d 0x%x\n",i, inbuf);
		int ret = conv_frame(inbuf, outbuf, height, width);
		if (ret < 0) {
			printf("frame ng\n");
		}

		size_t writesize = fwrite(outbuf, 1, output_framesize, output);
		if (writesize != output_framesize) {
            printf("fwrite err %d %d\n",writesize, output_framesize);
			return -1;
		} else {
		}

	}
	return 0;
}


//parameter1 input 1
//parameter2 input 2
//parameter3 height
//parameter4 width

int main(int argc, char** argv[])
{
	if (argc != 5) {
		printf("convyuv.exe input_filename output_filename height width\n");
		return -1;
	}
	FILE *input = fopen((const char*)argv[1], "r");
	if (input == NULL) {
		printf("can't open file\n");
		return -1;
	}

	FILE *output = fopen((const char*)argv[2], "w");
	if (output == NULL) {
		printf("can't open file\n");
		return -1;
	}

	int width = atoi((const char*)argv[3]);
	int height = atoi((const char*)argv[4]);

	int ret = conv_file(input, output, width, height);
	if (ret < 0) {
		printf("ng\n");
	}

	fclose(input);
	fclose(output);
	return 0;
}

