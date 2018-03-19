#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aviHeader.h"
#include "rawvideo420.h"
#include "v210.h"

struct RiffHeader kRiffHeader = 
{
    0x46464952, //RIFF
    0x3a62bb6,  //file_size;
};

uint32_t kAvi = 0x20495641;

struct ListHeader kListHeader = 
{
    0x5453494c,  //LIST
    0x20fe0,     //list_size;
    0x6c726468,  //hdrl
};
struct AviMainHeader kAviMainHeader =
{
    0x68697661, //fcc avih
    0x38,       //cb
    0x8256,     //dw_micro_sec_per_frame
    0x0,        //dw_max_bytes_per_sec
    0x1000,     //dw_padding_granularity
    0x10,       //dw_flag
    0xb,        //dw_total_frames
    0x0,        //dw_initial_frames
    0x2,        //dw_streams
    0x546000,   //dw_suggested_buffer_size
    0x780,      //dw_width
    0x438,      //dw_height
    0x0,        //dw_reserved
    0x0,        //dw_reserved
    0x0,        //dw_reserved
    0x0,        //dw_reserved
};
struct ListHeader kListHeader2 = 
{
    0x5453494c,  //LIST
    0x10074,     //list_size;
    0x6c727473,  //strh
};
struct AviStreamHeader kAviStreamHeader =
{
    0x68727473,    //fcc
    0x38,          //cb
    0x73646976,    //fcc_type
    0x30313276,    //fcc_header
    0x0,           //dw_flag
    0x0,           //w_priority
    0x0,           //w_language
    0x0,           //dw_initial_frames
    0x3e9,         //dw_scale
    0x7530,        //dw_rate
    0x0,           //dw_start
    0xb,           //dw_length
    0x546000,      //dw_suggested_buffer_size
    0x2648,        //dw_quality
    0x546000,      //dw_sample_size
    {
        0x0,       //left
        0x0,       //top
        0x0,       //right
        0x0,       //bottom
    },
};
uint32_t kStrf = 0x66727473;
uint32_t kStrfSize = 0x28;

struct BitMapInfo kBitMapInfo = 
{
    {
        0x28,       //bi_size
        0x780,      //bi_width
        0x438,      //bi_height
        0x1,        //bi_planes
        0x14,       //bi_bit_count
        0x30313276, //bi_compression
        0x546000,   //bi_size_image
        0x0,        //bi_x_pels_per_meter
        0x0,        //bii_y_pels_per_mster,
        0x0,        //bi_clr_used
        0x0,        //bi_clr_important
    }
};
uint32_t kIndxHeader = 0x78646e69;
uint32_t kIndxSize = 0xfff8;
uint8_t *kIndx=NULL;

struct AviSuperIndexChunk kAviSuperIndexChunk =
{
    0x78646e69, //fcc
    0xfff8,     //cb
    0x4,        //w_longs_per_entry
    0x0,        //b_index_sub_type
    0x0,        //b_index_type
    0x1,        //n_entries_in_use
    0x62643030, //dw_chunk_id
    0x0,        //reserved
    0x0,
    0x0,
};
struct AviSuperIndexEntry kAviSuperIndexEntry =
{
    0x3a41000,  //qw_offset
    0x10000,    //dw_size
    0xb,        //dw_duration
};

struct ListHeader kListHeader3 = 
{
    0x5453494c,  //LIST
    0x1005e,     //list_size;
    0x6c727473,  //hdrl
};

struct AviStreamHeader kAviStreamHeader2 =
{
    0x68727473,    //fcc
    0x38,          //cb
    0x73647561,    //fcc_type
    0x0,    //fcc_header
    0x0,           //dw_flag
    0x0,           //w_priority
    0x0,           //w_language
    0x0,           //dw_initial_frames
    0x1,         //dw_scale
    0xbb80,        //dw_rate
    0x0,           //dw_start
    0xe13a,           //dw_length
    0x307c8,      //dw_suggested_buffer_size
    0x0,        //dw_quality
    0x4,      //dw_sample_size
    {
        0x0,       //left
        0x0,       //top
        0x0,       //right
        0x0,       //bottom
    },
};
uint32_t kStrf2 = 0x66727473;
uint32_t kStrf2Size = 0x12;

struct WaveFormatX kWaveFormatX = 
{
    0x1,     //w_format_tag 
    0x2,     //n_channels
    0xbb80,  //n_samples_per_sec
    0x2ee00, //n_avg_byte_per_sec
    0x4,     //n_block_align
    0x10,    //w_bits_per_sample
    0x0,     //cb_size
};
uint32_t kIndxHeader2 = 0x78646e69;
uint32_t kIndxSize2 = 0xfff8;
uint8_t *kIndx2=NULL;

struct AviSuperIndexChunk kAviSuperIndexChunk2 =
{
    0x78646e69, //fcc
    0xfff8,     //cb
    0x4,        //w_longs_per_entry
    0x0,        //b_index_sub_type
    0x0,        //b_index_type
    0x1,        //n_entries_in_use
    0x62773130, //dw_chunk_id
    0x0,        //reserved
    0x0,
    0x0,
};
struct AviSuperIndexEntry kAviSuperIndexEntry2 =
{
    0x3a51000,  //qw_offset
    0x10000,    //dw_size
    0x44d2,     //dw_duration
};

uint32_t kJunkHeader = 0x4b4e554a;
uint32_t kJunkSize = 0x0eb2;
uint8_t  *kJunk = NULL;

struct ListHeader kListHeader4 = 
{
    0x5453494c,  //LIST
    0x3a40004,   //list_size;
    0x69766f6d,  //hdrl
};

uint32_t kVideoJunkHeader = 0x4b4e554a;
uint32_t kVideoJunkSize = 0xff0;
uint8_t  *kVideoJunk = NULL;

uint32_t kVideoHeader = 0x62643030;
uint32_t kVideoSize = 0x546000;
uint8_t  *kVideop = NULL;

uint32_t kAudioHeader = 0x62773130;
uint32_t kAudioSize = 0x307c8;
uint8_t  *kAudiop = NULL;

uint32_t kAudioJunkHeader = 0x4b4e554a;
uint32_t kAudioJunkSize = 0x830;
uint8_t  *kAudioJunk = NULL;


uint32_t kIx00Header = 0x30307869;
uint32_t kIx00HeaderSize = 0xfff8;
uint8_t *kIx00p = NULL;

struct AviStdIndex kAviStdIndex = 
{
    0x2,    //w_longs_per_entry
    0x0,    //b_index_sub_type
    0x1,    //b_index_type
    0xb,    //n_entries_in_use
    0x62643030, //dw_chunk_id
    0x0,        //dw_base_offset
};
struct AviStdIndexEntry kAviStdIndexEntry = 
{
    //0x22000,  //dw_offset
    0x21008,  //dw_offset
    0x546000, //dw_size
};
uint32_t kIx01Header = 0x31307869;
uint32_t kIx01HeaderSize = 0xfff8;
uint8_t *kIx01p = NULL;

struct AviStdIndex kAviStdIndex2 = 
{
    0x2,    //w_longs_per_entry
    0x0,    //b_index_sub_type
    0x1,    //b_index_type
    0x1,    //n_entries_in_use
    0x62773130, //dw_chunk_id
    0x0,        //dw_base_offset
};
#define MAX_AUDIO_NUM   (30)
struct AviStdIndexEntry kAviStdIndexEntry2[MAX_AUDIO_NUM] = 
{
//    0xa3bb000, //dww_offset
//    0x307c8, //dw_size
};
struct AviOldIndex kAviOldIndex =
{
    0x31786469, //fcc
    0xc0,       //cb
};
struct AviOldIndexEntry kAviOldIndexEntryVideo =
{
    0x62643030, //dw_chunk_id
    0x10,       //dw_flags
    0x21000,    //dw_offset
    0x546000,   //dw_size
};
struct AviOldIndexEntry kAviOldIndexEntryAudio =
{
    0x62773130, //dw_chunk_id
    0x10,       //dw_flags
    0x21ff8,    //dw_offset
    0x307c8,    //dw_size
};
//#define VIDEO_FRAME_NUM (0x24)
//#define VIDEO_FRAME_NUM (60)
//#define VIDEO_FRAME_NUM (32)
#define VIDEO_FRAME_NUM (300)
#define INPUT_DATA_SIZE (3110400)

int8_t* kInputBuffer;
int readFileHeader(FILE *file)
{
    int8_t tmp[256];
    int8_t *ret;
    for(int i =0;i<5;i++) { 
        ret = fgets(tmp, 256, file);
        if(ret == tmp) {
            int32_t cmpret;
            cmpret = strncmp(tmp, "FRAME", 5);
            if (cmpret == 0) {
                printf("get FRAME\n");
                break;
            } else {
                printf("%s\n", tmp);
            }

        } else {
            printf("err %d\n", __LINE__);
            return -1;
        }
    }
#if 0
    kInputBuffer = (int8_t*)malloc(INPUT_DATA_SIZE);
    if (kInputBuffer == NULL) {
        printf("err %d\n", __LINE__);
        return ;
    }
#endif
    setParamRawVideo420(1920, 1080);
    size_t inputframesize = getFrameSizeRawVideo420();
    kInputBuffer = (int8_t*)malloc(inputframesize);
    if (kInputBuffer == NULL) {
        printf("err %d\n", __LINE__);
        return -1;
    }
    setBufferRawVideo420(kInputBuffer);
    return 0;

}
int getFrame(FILE* file, int frame_num, uint8_t *buffer)
{
    size_t readsize;
    readsize = fread(kInputBuffer,  1, INPUT_DATA_SIZE, file);

    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return -1;
        //return ;
    } else if (readsize != INPUT_DATA_SIZE) {
        printf("err %d\n", __LINE__);
        return -1;
        //return ;
    } else {
    }

    setParamV210(1920, 1080);
    setBufferV210(buffer);

    int pixel_num = 1920 * 1080;
    unsigned short y,pb,pr;
    for(int i = 0;i< pixel_num;i++) {
        getPixelRawVideo420(i, &y, &pb, &pr);
        //y =  0x8000;
        //pb = 0x8000;
        //pr = 0x8000;
        //y =  0x8000;
        //pb = 0x8000;
        //pr = 0x8000;
        if (( i % 2) == 0 ) {
            setPixelv210(y, pb, pr, i);
        } else {
            setYPixelv210(y, i);
        }
    }
    //memcpy(buffer ,kInputBuffer , INPUT_DATA_SIZE);
    int8_t *ret;
    int8_t tmp[256];
    ret = fgets(tmp, 256, file);
    if(ret == tmp) {
        int32_t cmpret;
        cmpret = strncmp(tmp, "FRAME", 5);
        if (cmpret == 0) {
            printf("get FRAME\n");
            return 0;
        } else {
            printf("%s\n", tmp);
            return -1;
        }
    } else {
        printf("err %d\n", __LINE__);
        return -1;

    }
 
}
int getFrameNum(FILE *input)
{
    int ret=0;
    ret = readFileHeader(input);
    if (ret < 0) {
        return 0;
    }
    uint8_t * buf;
    buf = (uint8_t*)malloc(kVideoSize);
    int frame=0;
    for (frame=0;;frame++) {
        ret = getFrame(input, frame, buf);
        if (ret < 0) {
            break;
        }
    }
    ret = fseek(input, 0, SEEK_SET);
    if ( ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    if ((frame + 1) > 300) {
        return 300;
    } else {
        return (frame + 1);
    }

}
int conv_file2(FILE *input, FILE *output)
{
    int frame_num = 0;
    frame_num = getFrameNum(input);
    printf("frame num %d\n", frame_num);

    readFileHeader(input);
    int audio_counter = 0;
    //int num = VIDEO_FRAME_NUM;
    int num = frame_num;
    
    size_t writesize;
    writesize = fwrite(&kRiffHeader, 1, sizeof(kRiffHeader), output);
    if (writesize != sizeof(kRiffHeader)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kAvi, 1, sizeof(kAvi), output);
    if (writesize != sizeof(kAvi)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kListHeader ,  1, sizeof(kListHeader ), output);
    if (writesize != sizeof(kListHeader )) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    kAviMainHeader.dw_total_frams = num;
    writesize = fwrite(&kAviMainHeader , 1, sizeof(kAviMainHeader), output);
    if (writesize != sizeof(kAviMainHeader )) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kListHeader2, 1, sizeof(kListHeader2), output);
    if (writesize != sizeof(kListHeader2)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    kAviStreamHeader.dw_length = num;
    writesize = fwrite(&kAviStreamHeader , 1, sizeof(kAviStreamHeader ), output);
    if (writesize != sizeof(kAviStreamHeader )) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kStrf, 1, sizeof(kStrf), output);
    if (writesize != sizeof(kStrf)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kStrfSize , 1, sizeof(kStrfSize ), output);
    if (writesize != sizeof(kStrf)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kBitMapInfo , 1, sizeof(kBitMapInfo ), output);
    if (writesize != sizeof(kBitMapInfo )) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    kIndx = (uint8_t*)malloc(kIndxSize + 8);
    if (kIndx == NULL ) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    memset(kIndx, 0x0, kIndxSize);
    memcpy(kIndx, &kAviSuperIndexChunk, sizeof(kAviSuperIndexChunk));
    memcpy(kIndx + sizeof(kAviSuperIndexChunk), &kAviSuperIndexEntry, sizeof(kAviSuperIndexEntry));


    fpos_t k_indx_position;
    int ret = fgetpos(output, &k_indx_position);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(kIndx , 1, kIndxSize + 8, output);
    if (writesize != kIndxSize + 8 ) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kListHeader3 , 1, sizeof(kListHeader3 ), output);
    if (writesize != sizeof(kListHeader3 )) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    fpos_t k_avi_stream_header2_position;
    ret = fgetpos(output, &k_avi_stream_header2_position);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(&kAviStreamHeader2 , 1, sizeof(kAviStreamHeader2 ), output);
    if (writesize != sizeof(kAviStreamHeader2)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kStrf2, 1, sizeof(kStrf2), output);
    if (writesize != sizeof(kStrf2)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kStrf2Size , 1, sizeof(kStrf2Size ), output);
    if (writesize != sizeof(kStrf2)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kWaveFormatX , 1, WAVE_FORMAT_X_SIZE, output);
    if (writesize != WAVE_FORMAT_X_SIZE) {
        printf("err %d %d\n", __LINE__,sizeof(kWaveFormatX));
        return 0;
    }

    kIndx2 = (uint8_t*)malloc(kIndxSize2 + 8);
    if (kIndx2 == NULL ) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    memset(kIndx2, 0x0, kIndxSize2);
    memset(kIndx2, 0x0, kIndxSize2);
    memcpy(kIndx2, &kAviSuperIndexChunk2, sizeof(kAviSuperIndexChunk2));
    memcpy(kIndx2 + sizeof(kAviSuperIndexChunk2), &kAviSuperIndexEntry2, sizeof(kAviSuperIndexEntry2));

    fpos_t k_indx2_position;
    ret = fgetpos(output, &k_indx2_position);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(kIndx2 , 1, kIndxSize2 + 8, output);
    if (writesize != (kIndxSize2 + 8)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kJunkHeader , 1, sizeof(kJunkHeader), output);
    if (writesize != sizeof(kJunkHeader)) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    writesize = fwrite(&kJunkSize , 1, sizeof(kJunkSize ), output);
    if (writesize != sizeof(kJunkSize )) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    kJunk = (uint8_t*)malloc(kJunkSize);
    if (kJunk == NULL ) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    memset(kJunk , 0x0, kJunkSize);

    fpos_t pos;
    ret = fgetpos(output, &pos);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    //printf("1 pos=%d %x\n", pos,pos);

    writesize = fwrite(kJunk, 1, kJunkSize, output);
    if (writesize != kJunkSize) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    free(kJunk);

    fpos_t k_list_header4_position;
    ret = fgetpos(output, &k_list_header4_position);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(&kListHeader4 , 1, sizeof(kListHeader4 ), output);
    if (writesize != sizeof(kListHeader4 )) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    uint32_t key;
    uint32_t size;
    uint8_t *data;
    int i;
    for (i = 0;i<num;i++) {
        writesize = fwrite(&kVideoHeader , 1, sizeof(kVideoHeader), output);
        if (writesize != sizeof(kVideoHeader)) {
            printf("err %d\n", __LINE__);
            return 0;
        }
    
        writesize = fwrite(&kVideoSize , 1, sizeof(kVideoSize ), output);
        if (writesize != sizeof(kVideoSize )) {
            printf("err %d\n", __LINE__);
            return 0;
        }
    
        kVideop = (uint8_t*)malloc(kVideoSize);
        if (kVideop == NULL ) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        memset(kVideop , 0x0, kVideoSize);
        getFrame(input, i, kVideop);
        ret = fgetpos(output, &pos);
        if (ret < 0) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        //printf("v pos 0x%x\n",pos);
        //printf("0x%x\n", kVideop[0]);

        writesize = fwrite(kVideop, 1, kVideoSize, output);
        if (writesize != kVideoSize) {
            printf("err %d\n", __LINE__);
            return 0;
        }

        free(kVideop);
        writesize = fwrite(&kVideoJunkHeader , 1, sizeof(kVideoJunkHeader), output);
        if (writesize != sizeof(kVideoJunkHeader)) {
            printf("err %d\n", __LINE__);
            return 0;
        }
    
        writesize = fwrite(&kVideoJunkSize , 1, sizeof(kVideoJunkSize ), output);
        if (writesize != sizeof(kVideoJunkSize )) {
            printf("err %d\n", __LINE__);
            return 0;
        }
    
        kVideoJunk = (uint8_t*)malloc(kVideoJunkSize);
        if (kVideoJunk == NULL ) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        memset(kVideoJunk , 0x0, kVideoJunkSize);
        writesize = fwrite(&kVideoJunk, 1, kVideoJunkSize, output);
        if (writesize != kVideoJunkSize) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        free(kVideoJunk);


        if (i%31 == 30) {
            writesize = fwrite(&kVideoJunkHeader , 1, sizeof(kVideoJunkHeader), output);
            if (writesize != sizeof(kVideoJunkHeader)) {
                printf("err %d\n", __LINE__);
                return 0;
            }
        
            writesize = fwrite(&kVideoJunkSize , 1, sizeof(kVideoJunkSize ), output);
            if (writesize != sizeof(kVideoJunkSize )) {
                printf("err %d\n", __LINE__);
                return 0;
            }
        
            kVideoJunk = (uint8_t*)malloc(kVideoJunkSize);
            if (kVideoJunk == NULL ) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            memset(kVideoJunk , 0x0, kVideoJunkSize);
            writesize = fwrite(&kVideoJunk, 1, kVideoJunkSize, output);
            if (writesize != kVideoJunkSize) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            free(kVideoJunk);
    
            writesize = fwrite(&kAudioHeader , 1, sizeof(kAudioHeader), output);
            if (writesize != sizeof(kAudioHeader)) {
                printf("err %d\n", __LINE__);
                return 0;
            }
        
            writesize = fwrite(&kAudioSize , 1, sizeof(kAudioSize ), output);
            if (writesize != sizeof(kAudioSize )) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            ret = fgetpos(output, &pos);
            if (ret < 0) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            kAviStdIndexEntry2[audio_counter].dw_offset = pos;
            kAviStdIndexEntry2[audio_counter].dw_size = kAudioSize;
            audio_counter++;
        
            kAudiop = (uint8_t*)malloc(kAudioSize);
            if (kAudiop == NULL ) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            memset(kAudiop , 0x0, kAudioSize);
            writesize = fwrite(kAudiop, 1, kAudioSize, output);
            if (writesize != kAudioSize) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            free(kAudiop);

            writesize = fwrite(&kAudioJunkHeader , 1, sizeof(kAudioJunkHeader), output);
            if (writesize != sizeof(kAudioJunkHeader)) {
                printf("err %d\n", __LINE__);
                return 0;
            }
        
            writesize = fwrite(&kAudioJunkSize , 1, sizeof(kAudioJunkSize ), output);
            if (writesize != sizeof(kAudioJunkSize )) {
                printf("err %d\n", __LINE__);
                return 0;
            }
        
            kAudioJunk = (uint8_t*)malloc(kAudioJunkSize);
            if (kAudioJunk == NULL ) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            memset(kAudioJunk , 0x0, kAudioJunkSize);
            writesize = fwrite(&kAudioJunk, 1, kAudioJunkSize, output);
            if (writesize != kAudioJunkSize) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            free(kAudioJunk);
        }
    }
    if (i%31 != 30) {
        writesize = fwrite(&kVideoJunkHeader , 1, sizeof(kVideoJunkHeader), output);
        if (writesize != sizeof(kVideoJunkHeader)) {
            printf("err %d\n", __LINE__);
            return 0;
        }
    
        writesize = fwrite(&kVideoJunkSize , 1, sizeof(kVideoJunkSize ), output);
        if (writesize != sizeof(kVideoJunkSize )) {
            printf("err %d\n", __LINE__);
            return 0;
        }
    
        kVideoJunk = (uint8_t*)malloc(kVideoJunkSize);
        if (kVideoJunk == NULL ) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        memset(kVideoJunk , 0x0, kVideoJunkSize);
        writesize = fwrite(&kVideoJunk, 1, kVideoJunkSize, output);
        if (writesize != kVideoJunkSize) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        free(kVideoJunk);

        writesize = fwrite(&kAudioHeader , 1, sizeof(kAudioHeader), output);
        if (writesize != sizeof(kAudioHeader)) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        kAudioSize  = 0x7d20;
        writesize = fwrite(&kAudioSize , 1, sizeof(kAudioSize ), output);
        if (writesize != sizeof(kAudioSize )) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        ret = fgetpos(output, &pos);
        if (ret < 0) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        kAviStdIndexEntry2[audio_counter].dw_offset = pos;
        kAviStdIndexEntry2[audio_counter].dw_size = kAudioSize;
        audio_counter++;
    
        kAudiop = (uint8_t*)malloc(kAudioSize);
        if (kAudiop == NULL ) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        memset(kAudiop , 0x0, kAudioSize);
        writesize = fwrite(kAudiop, 1, kAudioSize, output);
        if (writesize != kAudioSize) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        free(kAudiop);

        writesize = fwrite(&kAudioJunkHeader , 1, sizeof(kAudioJunkHeader), output);
        if (writesize != sizeof(kAudioJunkHeader)) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        kAudioJunkSize  = 0x2d8;
        writesize = fwrite(&kAudioJunkSize , 1, sizeof(kAudioJunkSize ), output);
        if (writesize != sizeof(kAudioJunkSize )) {
            printf("err %d\n", __LINE__);
            return 0;
        }
    
        kAudioJunk = (uint8_t*)malloc(kAudioJunkSize);
        if (kAudioJunk == NULL ) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        memset(kAudioJunk , 0x0, kAudioJunkSize);
        writesize = fwrite(&kAudioJunk, 1, kAudioJunkSize, output);
        if (writesize != kAudioJunkSize) {
            printf("err %d\n", __LINE__);
            return 0;
        }
        free(kAudioJunk);

    }

    fpos_t ix00header_position;
    ret = fgetpos(output, &ix00header_position);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(&kIx00Header , 1, sizeof(kIx00Header), output);
    if (writesize != sizeof(kIx00Header)) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(&kIx00HeaderSize , 1, sizeof(kIx00HeaderSize), output);
    if (writesize != sizeof(kIx00HeaderSize)) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    kIx00p = (uint8_t*)malloc(kIx00HeaderSize);
    if (kIx00p == NULL) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    memset(kIx00p, 0x0, kIx00HeaderSize);
    kAviStdIndex.n_entries_in_use = num;
    memcpy(kIx00p, &kAviStdIndex, sizeof(kAviStdIndex));
    for (int m = 0;m < num;m++) {
        memcpy(kIx00p + sizeof(kAviStdIndex) + (sizeof(kAviStdIndexEntry ) * m), &kAviStdIndexEntry, sizeof(kAviStdIndexEntry )) ;
        kAviStdIndexEntry.dw_offset += 0x547000;
        if (m%31 == 30) {
            kAviStdIndexEntry.dw_offset += 0x32000;
        }
    }

    writesize = fwrite(kIx00p, 1, kIx00HeaderSize, output);
    if (writesize != kIx00HeaderSize) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    free(kIx00p);

    fpos_t ix01header_position;
    ret = fgetpos(output, &ix01header_position);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(&kIx01Header , 1, sizeof(kIx01Header), output);
    if (writesize != sizeof(kIx01Header)) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(&kIx01HeaderSize , 1, sizeof(kIx00HeaderSize), output);
    if (writesize != sizeof(kIx01HeaderSize)) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    kIx01p = (uint8_t*)malloc(kIx01HeaderSize);
    if (kIx01p == NULL) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    memset(kIx01p, 0x0, kIx01HeaderSize);
    int audio_num = 0;
    if ((num % 31) == 0) {
        kAviStdIndex2.n_entries_in_use = (num / 31) ;
        audio_num = (num / 31);
    } else {
        kAviStdIndex2.n_entries_in_use = (num / 31) + 1;
        audio_num = (num / 31) + 1;
    }
    kAviStdIndex2.n_entries_in_use = (num / 31) + 1;
    memcpy(kIx01p, &kAviStdIndex2, sizeof(kAviStdIndex2));
    memcpy(kIx01p + sizeof(kAviStdIndex2), &kAviStdIndexEntry2, sizeof(struct AviStdIndexEntry) * audio_counter);


    writesize = fwrite(kIx01p , 1, kIx01HeaderSize, output);
    if (writesize != kIx01HeaderSize) {
        printf("err %d\n", __LINE__);
        return 0;
    }


    fpos_t idx1_position;
    ret = fgetpos(output, &idx1_position);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    kAviOldIndex.cb = (num * sizeof(kAviOldIndexEntryVideo)) + (audio_counter * sizeof(kAviOldIndexEntryVideo));
    writesize = fwrite(&kAviOldIndex , 1, sizeof(kAviOldIndex ), output);
    if (writesize != sizeof(kAviOldIndex )) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    int p = 0;
    for (p = 0;p<num;p++) {
        writesize = fwrite(&kAviOldIndexEntryVideo , 1, sizeof(kAviOldIndexEntryVideo ), output);
        if (writesize != sizeof(kAviOldIndexEntryVideo)) {
            printf("err %d\n", __LINE__);
            return 0;
        }

        if (p%31 == 30) {
            kAviOldIndexEntryAudio.dw_offset =  kAviOldIndexEntryVideo.dw_offset + 0x547ff8;
            writesize = fwrite(&kAviOldIndexEntryAudio , 1, sizeof(kAviOldIndexEntryAudio ), output);
            if (writesize != sizeof(kAviOldIndexEntryAudio)) {
                printf("err %d\n", __LINE__);
                return 0;
            }
            kAviOldIndexEntryVideo.dw_offset += 0x579000;
        } else {
            kAviOldIndexEntryVideo.dw_offset += 0x547000;
        }
    }
    if (p%31 != 30) {
        kAviOldIndexEntryAudio.dw_offset =  kAviOldIndexEntryVideo.dw_offset + 0xff8;
        kAviOldIndexEntryAudio.dw_size =  0x7d20;
        writesize = fwrite(&kAviOldIndexEntryAudio , 1, sizeof(kAviOldIndexEntryAudio ), output);
        if (writesize != sizeof(kAviOldIndexEntryAudio)) {
            printf("err %d\n", __LINE__);
            return 0;
        }
    }
    fpos_t end_of_file;
    ret = fgetpos(output, &end_of_file);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    //file_size
    ret = fseek(output, 4, SEEK_SET);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    int32_t file_size = end_of_file - 8;
    writesize = fwrite(&file_size , 1, 4, output);
    if (writesize != 4) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    //dw_total_frams
    //dw_length
    //
    //
    //
    //qw_offset ... audio offset
    //dw_duration 
    kAviSuperIndexEntry.qw_offset = ix00header_position;
    kAviSuperIndexEntry.dw_duration = num;
    memcpy(kIndx + sizeof(kAviSuperIndexChunk), &kAviSuperIndexEntry, sizeof(kAviSuperIndexEntry));

    ret = fseek(output, k_indx_position, SEEK_SET);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(kIndx , 1, kIndxSize + 8, output);
    if (writesize != (kIndxSize + 8)) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    
    //dw_length audio size
    //dw_suggested_buffer
    ret = fseek(output, k_avi_stream_header2_position, SEEK_SET);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    kAviStreamHeader2.dw_length = 0x10d04;
    kAviStreamHeader2.dw_suggested_buffer_size = 0x307c4;
    //
    //
    //qw_offset ... audio offset
    //dw_duration 
    kAviSuperIndexEntry2.qw_offset = ix01header_position;
    kAviSuperIndexEntry2.dw_duration = 0xe13a;
    memcpy(kIndx2 + sizeof(kAviSuperIndexChunk), &kAviSuperIndexEntry2, sizeof(kAviSuperIndexEntry2));

    ret = fseek(output, k_indx2_position, SEEK_SET);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    writesize = fwrite(kIndx2 , 1, kIndxSize2 + 8, output);
    if (writesize != (kIndxSize2 + 8)) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    
    //LIST size
    ret = fseek(output, k_list_header4_position , SEEK_SET);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    kListHeader4.list_size = idx1_position - (k_list_header4_position + 8);
    writesize = fwrite(&kListHeader4 , 1, sizeof(kListHeader4 ), output);
    if (writesize != sizeof(kListHeader4 )) {
        printf("err %d\n", __LINE__);
        return 0;
    }

    fclose(output);

}

//parameter1 input 
//parameter2 output

int main(int argc, char** argv[])
{
	if (argc != 3) {
		printf("y4m2avi.exe input_filename output_filename\n");
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

	int ret = conv_file2(input, output);
	if (ret < 0) {
		printf("ng\n");
	}

	fclose(input);
	fclose(output);
	return 0;
}

