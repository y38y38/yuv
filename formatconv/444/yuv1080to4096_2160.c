#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void copy_hd_to_4k( uint16_t*dst, int16_t *src)
{
    int32_t dst_horizontal = 4096;
    int32_t dst_vertical = 2160;
    int32_t src_horizontal = 1920;
    int32_t src_vertical = 1080;

    for (int j=0;j< src_vertical;j++) {
        //top left
        memcpy(dst + (j * dst_horizontal), 
               src + (j * src_horizontal) , src_horizontal * 2);

        //top right
        memcpy(dst + (j * dst_horizontal) + src_horizontal,  
               src + (j * src_horizontal) , src_horizontal * 2);

        //down left
        memcpy(dst + (((dst_horizontal/2) * src_vertical) * 2) + (j * dst_horizontal) , 
               src + (j * src_horizontal) , src_horizontal * 2);
        //down right
        memcpy(dst + (((dst_horizontal/2) * src_vertical) * 2) + (j * dst_horizontal) + (src_horizontal),
               src + (j* src_horizontal) , src_horizontal * 2);
    }
    return;
}
/* input is 444 16bit */
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
    uint32_t src_size = ((1920*1080)*2) *3;
    uint16_t *src_data = (uint16_t*)malloc(src_size);
    if (src_data == NULL) {
        printf("%d\n", __LINE__);
        return 0;
    }
    uint32_t dst_size = ((2048*1080)*2) *3 * 4;
    uint16_t *dst_data = (uint16_t*)malloc(dst_size);
    if (dst_data == NULL) {
        printf("%d\n", __LINE__);
        return 0;
    }
    for(int i=0;i<(2048*1080*4*3);i++) {
        *(dst_data + i) = 0x200;
    }
    for (int i=0;;i++) {
        size_t readsize = fread(src_data, 1, src_size, input);
        if (readsize != src_size) {
            printf("%d %d\n", __LINE__, (int)readsize);
            break;
        }
        //y
        copy_hd_to_4k(dst_data, src_data);


        //cb
        copy_hd_to_4k(dst_data + (4096*2160), src_data + (1920*1080));

        //cr
        copy_hd_to_4k(dst_data + (4096*2160) * 2, src_data + (1920*1080)*2);

        size_t writesize = fwrite(dst_data, 1, dst_size,  output);
        if (writesize != dst_size) {
            printf("%s %d %d\n", __FUNCTION__, __LINE__, (int)writesize);
            //printf("write %d %p %d %p \n", (int)writesize, raw_data, raw_size,output);
            return -1;
        }
        if (i==0) {
          //break;
        }
        //printf("end frame\n");
        printf(".");
    }

    return 0;
}

