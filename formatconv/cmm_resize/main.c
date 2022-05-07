#include  <stdio.h>
#include  <stdlib.h>

#include "cmm2cmm.h"



int conv_frame(unsigned char *input, unsigned char *output, int input_width, int input_height, int output_width, int output_height)
{
	return cmm2cmm(input, output,input_width, input_height, output_width,  output_height);
}

int conv_file(FILE *input, FILE *output, int input_width, int input_height, int output_width, int output_height)
{

	void *inbuf;
	void *outbuf;
    int i;

	int input_framesize = inputFrameSize(input_width, input_height);
	inbuf = malloc(input_framesize);
	printf("i %d\n", input_framesize);

	if (inbuf == NULL) {
		printf("err malloc 1\n");
		return -1;
	}

	int output_framesize = outputFrameSize(output_width ,output_height);
	printf("o %d\n", output_framesize);

	outbuf = malloc(output_framesize);
	if (outbuf == NULL) {
		printf("err malloc 2\n");
		return -1;
	}
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

		int ret = conv_frame(inbuf, outbuf, input_width, input_height, output_width, output_height);
		if (ret < 0) {
			printf("frame ng\n");
		}

		size_t writesize = fwrite(outbuf, 1, output_framesize, output);
//            printf("fwrite err %d %d\n",writesize, output_framesize);
		if (writesize != output_framesize) {
            printf("fwrite err %d %d\n",writesize, output_framesize);
			return -1;
		} else {
		}


	}
	free(inbuf);
	free(outbuf);
	return 0;
}


//parameter1 input file name
//parameter2  output file name
//parameter3 height
//parameter4 width
//parameter3 height
//parameter4 width

int main(int argc, char** argv[])
{
	if (argc != 7) {
		printf("cmm_resize input_filename output_filename input_height input_width output_height output_width\n");
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

	int input_width = atoi((const char*)argv[3]);
	int input_height = atoi((const char*)argv[4]);
	int output_width = atoi((const char*)argv[5]);
	int output_height = atoi((const char*)argv[6]);


	int ret = conv_file(input, output, input_width, input_height, output_width, output_height);
	if (ret < 0) {
		printf("ng\n");
	}

	fclose(input);
	fclose(output);
	return 0;
}

