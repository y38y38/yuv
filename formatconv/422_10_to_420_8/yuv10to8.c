#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int main(int argc, char **argv)
{
    if (argc != 5) {
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
    int horizontal = atoi(argv[3]);
    int vertical = atoi(argv[4]);
    uint32_t src_size = ((horizontal*vertical) * 2 ) + ((horizontal*vertical) * 2) ;
    uint16_t *src_data = (uint16_t*)malloc(src_size);
    if (src_data == NULL) {
        printf("%d\n", __LINE__);
        return 0;
    }
    uint32_t dst_size = (horizontal*vertical) + (horizontal*vertical) ;
    uint8_t *dst_data = (uint8_t*)malloc(dst_size);
    if (dst_data == NULL) {
        printf("%d\n", __LINE__);
        return 0;
    }
    for (int i=0;;i++) {
        size_t readsize = fread(src_data, 1, src_size, input);
        if (readsize != src_size) {
            if (readsize != 0)  {
                printf("%d %d\n", __LINE__, (int)readsize);
            }
            break;
        }
        int j;
        for (j=0;j<(horizontal*vertical*2);j++) {
            dst_data[j] = (uint8_t)(src_data[j] >> 2); 
        }

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
        //printf(".");
    }

    return 0;
}

