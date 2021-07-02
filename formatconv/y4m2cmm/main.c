#include  <stdio.h>
#include  <stdlib.h>
#include <string.h>



int conv_frame(unsigned char *input, unsigned char *output, int height, int width)
{
//	return yuv42cmm(input, output, height, width);
}


char *search_get(char *ptr, char *search_start, char *search_end, char *buf, int buf_len) {
	//search W
	char * start = strstr(ptr, search_start);
	if (start == NULL) {
		printf("%d\n", __LINE__);
		return NULL;
	}

	char *end = strstr(start ,search_end);
	if (end == NULL) {
		printf("%d %x\n", __LINE__ , *search_end);
		return NULL;
	}


	memset(buf, 0x0, buf_len);
	memcpy(buf, start , end - start);
	return start;
}

int conv_file(FILE *input, FILE *output)
{

	void *inbuf;
	void *outbuf;
    int i;


	char header[100];

	size_t readsize = fread(header, 1, 100, input);
	if (readsize != 100) {
		printf("read size header err %d\n", (int)readsize);
		return -1;
	}

	int len = strlen("YUV4MPEG2");

	if (strncmp(header, "YUV4MPEG2", len) != 0) {
		printf("file not y4m");
		return -1;
	}

	//search W
	char buf[1024];
	char * ptr = search_get(&header[len], "W", " ", buf, 1024);

	int width = atoi(buf+1);
	printf("width %d\n", width);

	ptr = search_get(ptr + strlen(buf), "H", " ",buf, 1024);

	int height = atoi(buf+1);
	printf("height %d\n", height);

	ptr = search_get(ptr + strlen(buf), "C420p10", "\n",buf , 1024);
	if (ptr == NULL) {
		printf("err %d \n", __LINE__);
		return -1;
	}
	//17694720
	int frame_size = (width * height * 2) + ((width/2) * (height/2) * 4);
	int y_frame_size = width * height *2;
	int c_frame_size = (width/2) * (height/2) *2;
	int c_422_frame_size = (width/2) * height * 2;

	int header_size = strlen("FRAME ");
	char *video_buffer = (char*) malloc(frame_size + header_size);
	if (video_buffer == NULL) {
		printf("err %d\n", __LINE__);
		return -1;
	}
	char *video_c_buffer  = (char*)malloc(c_422_frame_size);
	if (video_c_buffer == NULL) {
		printf("err %d\n", __LINE__);
		return -1;
	}

	ptr = search_get(ptr + strlen(buf), "FRAME", "\n", buf , 1024);
	if (ptr == NULL) {
		printf("err %d\n", __LINE__);
		return -1;
	}
	printf("%p %d\n", ptr, (int)(ptr - header));
	printf("%d %x\n", frame_size, frame_size);

	int ret = fseek(input, ptr -header, SEEK_SET);

	int frame_num =0;
	for (;;) {
		readsize = fread(video_buffer, 1, frame_size+header_size, input);
		if (readsize != frame_size+header_size) {
			printf("read size header err %d\n", (int)readsize);
			break;
		}
#if 0


		printf("%p\n", video_buffer);
		ptr = strstr(video_buffer, "FRAME");
		if (ptr == NULL) {
			printf("err %d\n", __LINE__);
		}
		printf("%p\n", ptr);
		ptr = strstr(ptr, "FRAME");
		if (ptr == NULL) {
			printf("err %d\n", __LINE__);
		}
		printf("%p\n", ptr);
#endif

		if (strncmp(video_buffer, "FRAME", strlen("FRAME"))) {
			printf("header err %x  %d\n", video_buffer[0], frame_num);
			return -1;
		}
		size_t writesize = fwrite(video_buffer+header_size, 1, y_frame_size, output);
		if (writesize != y_frame_size) {
			printf("writesize size header err %d %d\n", (int)writesize, __LINE__);
			break;
		}

		for(int i=0;i<height;i++) {
			writesize = fwrite(video_buffer+header_size+y_frame_size+(i*(width/2)*2), 1, (width), output);
			if (writesize != (width)) {
				printf("writesize size header err %d %d %d\n", (int)writesize, __LINE__,i);
				break;
			}
			writesize = fwrite(video_buffer+header_size+y_frame_size+(i*(width/2)*2), 1, (width), output);
			if (writesize != (width)) {
				printf("writesize size header err %d %d %d\n", (int)writesize, __LINE__,i);
				break;
			}
		}
		break;
		frame_num++;
	}
	printf("%d\n",frame_num);

#if 0


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

#endif
	return 0;
}


//parameter1 input 
//parameter2 output

int main(int argc, char** argv[])
{
	if (argc != 3) {
		printf("param err\n");
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

