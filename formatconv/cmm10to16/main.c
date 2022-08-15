#include  <stdio.h>
#include  <stdlib.h>


int conv_file(FILE *input, FILE *output)
{

	unsigned short inbuf;
	unsigned short outbuf;
	for (int i=0;;i++) {

		size_t readsize = fread(&inbuf, 1, 2, input);
        if (readsize == 0 ) {
//d            printf("OK end of file %d\n", i);
            return 0;
        } else if (readsize != 2) {
            printf("fread err\n");
			return -1;
		} else {
		}
		outbuf = inbuf << 6;
		unsigned short tmp2 = (short)outbuf;
		tmp2 = tmp2 - 32768;
		tmp2 = 32768;
//tmp2 = 0xFFFF;
		size_t writesize = fwrite(&outbuf, 1, 2, output);
//            printf("fwrite err %d %d\n",writesize, output_framesize);
		if (writesize != 2) {
            printf("fwrite err %d %d\n",writesize, 2);
			return -1;
		} else {
		}


	}
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
	if (argc != 3) {
		printf("cmm12_16 input_filename output_filename\n");
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

	int ret = conv_file(input, output);
	if (ret < 0) {
		printf("ng\n");
	}

	fclose(input);
	fclose(output);
	return 0;
}

