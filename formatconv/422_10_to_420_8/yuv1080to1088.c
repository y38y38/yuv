#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("error %d\n", __LINE__);
        return -1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("err %s\n", argv[1]);
        return -1;
    }
    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("err %s\n", argv[2]);
        return -1;
    }
    uint32_t src_size = (1920*1080) + ((1920*1080) / 2);
    uint8_t *src_data = (uint8_t*)malloc(src_size);
    if (src_data == NULL) {
        printf("%d\n", __LINE__);
        return 0;
    }
    uint32_t dst_size = (1920*1088) + ((1920*1088) /2 );
    uint8_t *dst_data = (uint8_t*)malloc(dst_size);
    if (dst_data == NULL) {
        printf("%d\n", __LINE__);
        return 0;
    }
    for (int i=0;;i++) {
        size_t readsize = fread(src_data, 1, src_size, input);
        if (readsize != src_size) {
            printf("%d %d\n", __LINE__, (int)readsize);
            break;
        }
        //y
        memcpy(dst_data, src_data, 1920*1080);
        int j;
        for(j=0;j<8;j++) {
            memcpy(dst_data + 1920*1080 + (j*1920), src_data + (1920*1079), 1920);
        }

        //cb
        memcpy(dst_data + (1920*1088), src_data + (1920*1080), (1920*1080) / 4);

        for(j=0;j<4;j++) {
            memcpy(dst_data + (1920*1088) + ((1920*1080) / 4) + (j * 960 ), src_data + (1920*1080) + (960 * 539), 960);
        }

        //cr
        memcpy(dst_data + (1920*1088) + (960*544), src_data + (1920*1080) + (960*540), (1920*1080) / 4);

        for(j=0;j<4;j++) {
            memcpy(dst_data + (1920*1088) + (960*544) + ((1920*1080) / 4) + (j * 960 ), src_data + (1920*1080) + (960*540) + (960 * 539), 960);
        }

        size_t writesize = fwrite(dst_data, 1, dst_size,  output);
        if (writesize != dst_size) {
            printf("%s %d %d\n", __FUNCTION__, __LINE__, (int)writesize);
            //printf("write %d %p %d %p \n", (int)writesize, raw_data, raw_size,output);
            return -1;
        }
        if (i==0) {
          break;
        }
        //printf("end frame\n");
        printf(".");
    }

    return 0;
}

