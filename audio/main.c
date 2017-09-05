#include <stdio.h>
#include  <stdlib.h>
#include "opus.h" 
#include "lib_enc_g711/enc_g711.h"

#define SEND_INTERVAL	(1) //sample@48kHz
#define	LPCM_BIT		(16) //

void NotifyEnd(unsigned long id)
{
	printf("%s %d\n", __FUNCTION__, (int)id);
	return;
}
//int main(int argc, char** argv[])
int main(int argc, char** argv)
{
	
	EncG711RegisterFunc(NotifyEnd);

	if (argc != 5) {
		printf("convyuv.exe input_filename output_filename height width\n");
		return -1;
	}
	FILE *input = fopen((const char*)argv[1], "r");
	if (input == NULL) {
		printf("can't open file\n");
		return -1;
	}

	int i;
	for (i = 0;i < 0x100;i++) {
		EncG711Send(i, 0x0, 0x10);
	}
	return 0;
}
