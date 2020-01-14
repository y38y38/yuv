#include <stdio.h>

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
    uint32_t size = 1920*1080 * 2;
    uint16_t *yuv_data = (uint16_t*)malloc(size);
    if (yuv_data == NULL) {
        printf("%d\n", __LINE__);
        return 0;
    }
    uint32_t size = 1920*1080 * 2 * 2;
    uint16_t *yuv_data = (uint16_t*)malloc(size);
    if (yuv_data == NULL) {
        printf("%d\n", __LINE__);
        return 0;
    }
    for (int i=0;;i++) {
        size_t readsize = fread(yuv_data, 1, size, input);
        if (readsize != size) {
            printf("%d %d\n", __LINE__, (int)readsize);
            break;
        }
        int j;
        for(j=0;j<(1920*1080*2);j++) {
        }

        size_t writesize = fwrite(frame, 1, frame_size,  output);
        if (writesize != frame_size) {
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
    free(y_data);
    free(cb_data);
    free(cr_data);
    fclose(input);
    fclose(output);

    return 0;
}

