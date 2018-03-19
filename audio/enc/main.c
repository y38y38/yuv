#include <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "opus.h" 

#define LPCM_SAMPLING_RATE  (48000)
#define CH_NUM  (1)

#define LPCM_BYTE		(2)
#define LPCM_SAMPLE     (960)

#define OPUS_BITRATE    (64000) 
#define OPUS_OUTBUF_SIZE   (4000) /* 1066.6666...byte */

#define LPCM_HEAD_SIZE_MAX  (200)

int getDataStrPointer(char *buf)
{
    return
}
int getWaveDataSize(char *filename)
{
	FILE *input = fopen((const char*)filename, "r");
	if (input == NULL) {
		printf("can't open file\n");
		return -1;
	}
    unsigned char *inbuf  = (unsigned char*)malloc(LPCM_HEAD_SIZE_MAX);
    if (inbuf == NULL) {
        return -1;
    }

	size_t readsize = fread(inbuf, 1, LPCM_HEAD_SIZE_MAX , input);
    if (readsize == 0 ) {
        printf("err\n");
        fclose(input);
        return -1;
    } else if (readsize != LPCM_HEAD_SIZE_MAX) {
        printf("size is little err\n");
        fclose(input);
        return -1;
	} else {
	}

    int i;
    unsigned long data_size;
    //unsigned long data_value = 0x64617461; //data
    unsigned long data_value = 0x61746164; //data
    for(i = 0;i < LPCM_HEAD_SIZE_MAX ;i++) {
        // search data
        if (memcmp((inbuf+i), &data_value, 4) == 0) {
            data_size = *((unsigned long*)(inbuf + (i + 4)));
            fclose(input);
            return data_size;
        } else {
        }
    }
    printf("file is no wav\n");
    fclose(input);
    return 0;
}

int main(int argc, char** argv)
{
	

	if (argc != 3) {
		printf("opusenc.exe input_filename output_filename\n");
		return -1;
	}
    int lpcm_raw_size = getWaveDataSize(argv[1]);
    printf("raw_size %d\n", lpcm_raw_size);

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
	encoder = opus_encoder_create(LPCM_SAMPLING_RATE, CH_NUM, OPUS_APPLICATION_VOIP, &error);
	if (error < 0) {
		printf("%d\n", error);
		return -1;
	}
    opus_encoder_ctl(encoder, OPUS_SET_BITRATE(OPUS_BITRATE));
    //opus_encoder_ctl(encoder, OPUS_SET_COMPLEXITY(0));
    //opus_encoder_ctl(encoder, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));

    unsigned char *outbuf= (unsigned char*)malloc(OPUS_OUTBUF_SIZE);
    if (outbuf== NULL) {
        return -1;
    }

    unsigned char *inbuf  = (unsigned char*)malloc(LPCM_SAMPLE * LPCM_BYTE);
    if (inbuf == NULL) {
        return -1;
    }

    int i;
	for (i=0;;i++) {
		size_t readsize = fread(inbuf, LPCM_BYTE * CH_NUM, LPCM_SAMPLE, input);
        if (readsize == 0 ) {
            printf("OK end of file %d\n", i);
            return 0;
        } else if (readsize != (LPCM_SAMPLE )) {
            printf("OK end of file %d %d\n", (int)readsize, i);
			return 0;
		} else {
		}
        int len = opus_encode(encoder, (opus_int16*)inbuf, LPCM_SAMPLE, outbuf, OPUS_OUTBUF_SIZE);

		if (len < 0) {
            if (OPUS_BAD_ARG == len ) {
			    printf("OPUS_BAD_ARG\n");
            } else if (OPUS_BUFFER_TOO_SMALL == len) {
			    printf("OPUS_BUFFER_TOO_SMALL\n");
            } else if (OPUS_INTERNAL_ERROR == len ) {
			    printf("OPUS_INTERNAL_ERROR\n");
            } else if (OPUS_INVALID_PACKET == len) {
			    printf("OPUS_INVALID_PACKET\n");
            } else if (OPUS_UNIMPLEMENTED == len) {
			    printf("OPUS_UNIMPLEMENTED\n");
            } else if (OPUS_ALLOC_FAIL == len) {
			    printf("OPUS_ALLOC_FAIL\n");
            } else {
			    printf(" else error\n");
            }
			printf("frame ng len=%d %d\n", len, i);
		} else {
			printf("len = %d\n", len);
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
    opus_encoder_destroy(encoder);

	return 0;
}
