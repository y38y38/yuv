#include <stdio.h>
#include  <stdlib.h>
#include "opus.h" 

#define	LPCM_BYTE		(2)
#define LPCM_SMAPLE     (120)


int main(int argc, char** argv)
{
	

	if (argc != 3) {
		printf("opusenc.exe input_filename output_filename\n");
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

	OpusEncoder *encoder;
	int error;
	encoder = opus_encoder_create(48000, 1, OPUS_APPLICATION_VOIP, &error);
	if (error < 0) {
		printf("%d\n", error);
		return -1;
	}
    opus_encoder_ctl(encoder, OPUS_SET_BITRATE(64000));
    opus_encoder_ctl(encoder, OPUS_SET_COMPLEXITY(0));
    opus_encoder_ctl(encoder, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));

    unsigned char *outbuf= (unsigned char*)malloc(4000);
    if (outbuf== NULL) {
        return -1;
    }

    unsigned char *inbuf  = (unsigned char*)malloc(16000);
    if (inbuf == NULL) {
        return -1;
    }

    int i;
	for (i=0;;i++) {
		size_t readsize = fread(inbuf, 1, LPCM_SMAPLE, input);
        if (readsize == 0 ) {
            printf("OK end of file %d\n", i);
            return 0;
        } else if (readsize != LPCM_SMAPLE) {
            printf("OK end of file %d %d\n", (int)readsize, i);
			return 0;
		} else {
		}

        int len = opus_encode(encoder, (opus_int16*)inbuf, LPCM_SMAPLE, outbuf, 4000);
		if (len < 0) {
			printf("frame ng\n");
		}

		size_t writesize = fwrite(outbuf, 1, len , output);
//            printf("fwrite err %d %d\n",writesize, len);
		if (writesize != len) {
            printf("fwrite err %d %d\n",(int)writesize, len);
			return -1;
		} else {
		}

	}
	fclose(input);
	fclose(output);

	return 0;
}
