#include <stdio.h>
#include  <stdlib.h>
#include "opus.h" 

#define SEND_INTERVAL	(1) //sample@48kHz
#define	LPCM_BIT		(16) //

void NotifyEnd(unsigned long id)
{
	printf("%s %d\n", __FUNCTION__, (int)id);
	return;
}
int main(int argc, char** argv)
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
	OpusEncoder *encoder;
	int error;
	encoder = opus_encoder_create(48000, 1, OPUS_APPLICATION_VOIP, &error);
	if (error < 0) {
		printf("%d\n", error);
		return -1;
	}
	opus_encoder_ctl(encoder, OPUS_SET_BITRATE(500));
	opus_encoder_ctl(encoder, OPUS_SET_COMPLEXITY(0));
	opus_encoder_ctl(encoder, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));


	return 0;
}
