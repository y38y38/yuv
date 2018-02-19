#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aviHeader.h"


int conv_file(FILE *input, FILE *output)
{
    struct RiffHeader riff_header;
    size_t readsize = fread(&riff_header, 1, sizeof(riff_header), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(riff_header)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }

    //header check
    if (riff_header.riff != 0x46464952) {//RIFF
        printf("not riff 0x%x\n", riff_header.riff);
        return 0;
    }
    printf("riff = 0x%x\n", riff_header.riff);
    printf("file_size = 0x%x\n", riff_header.file_size);
    printf("\n");

    uint32_t avi;
    readsize = fread(&avi, 1, sizeof(avi), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != 4) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    //avi check
    if (avi != 0x20495641) { //AVI
        printf("not avi 0x%x\n", avi);
        return 0;
    }
    printf("avi=0x%x\n", avi);
    printf("\n");

    struct ListHeader list_header;
    readsize = fread(&list_header, 1, sizeof(list_header), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(list_header)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    //list header check
    if (list_header.list != 0x5453494c) { //LIST
        printf("err %d\n", __LINE__);
        return -1;
    }
    printf("LIST header 0x%x\n", list_header.list);
    printf("LIST size   0x%x\n", list_header.list_size);
    printf("LIST ttype  0x%x\n", list_header.list_ttype);
    printf("\n");

    struct AviMainHeader avi_main_header;
    readsize = fread(&avi_main_header, 1, sizeof(avi_main_header), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(avi_main_header)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    if (avi_main_header.fcc == 0x38686976) {
        printf("err %d\n", __LINE__);
        return -1;
    }
    printf("\navi main header\n");
    printf("fcc 0x%x\n", avi_main_header.fcc);
    printf("cb 0x%x\n",avi_main_header.cb);
    printf("dw_micro_sec_per_frame 0x%x\n",avi_main_header.dw_micro_sec_per_frame);
    printf("dw_max_bytes_per_sec 0x%x\n",avi_main_header.dw_max_bytes_per_sec);
    printf("dw_padding_granularity 0x%x\n",avi_main_header.dw_padding_granularity);
    printf("dw_flag 0x%x\n",avi_main_header.dw_flag);
    printf("dw_total_frams 0x%x\n",avi_main_header.dw_total_frams);
    printf("dw_initial_frames 0x%x\n",avi_main_header.dw_initial_frames);
    printf("dw_streams 0x%x\n",avi_main_header.dw_streams);
    printf("dw_suggested_buffer_size 0x%x\n",avi_main_header.dw_suggested_buffer_size);
    printf("dw_width 0x%x\n",avi_main_header.dw_width);
    printf("dw_height 0x%x\n",avi_main_header.dw_height);
    printf("\n");

    struct ListHeader list_header2;
    readsize = fread(&list_header2, 1, sizeof(list_header2), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(list_header2)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    //list header check
    if (list_header2.list != 0x5453494c) { //LIST
        printf("err %d\n", __LINE__);
        return -1;
    }
    printf("LIST header 0x%x\n", list_header2.list);
    printf("LIST size   0x%x\n", list_header2.list_size);
    printf("LIST ttype  0x%x\n", list_header2.list_ttype);
    printf("\n");

    struct AviStreamHeader avi_stream_header;
    readsize = fread(&avi_stream_header, 1, sizeof(avi_stream_header), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(avi_stream_header)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    //avi stream header check
    if (avi_stream_header.fcc != 0x68727473) { //strh
        printf("err %d\n", __LINE__);
        return -1;
    }
    printf("\navi stream header\n");
    printf("fcc=0x%x\n",avi_stream_header.fcc);
    printf("cb=0x%x\n",avi_stream_header.cb);
    printf("fcc_type=0x%x\n",avi_stream_header.fcc_type);
    printf("fcc_header=0x%x\n",avi_stream_header.fcc_header);
    printf("dw_flag=0x%x\n",avi_stream_header.dw_flag);
    printf("w_priority=0x%x\n",avi_stream_header.w_priority);
    printf("w_language=0x%x\n",avi_stream_header.w_language);
    printf("dw_initial_frames=0x%x\n",avi_stream_header.dw_initial_frames);
    printf("dw_scale=0x%x\n",avi_stream_header.dw_scale);
    printf("dw_rate=0x%x\n",avi_stream_header.dw_rate);
    printf("dw_start=0x%x\n",avi_stream_header.dw_start);
    printf("dw_length=0x%x\n",avi_stream_header.dw_length);
    printf("dw_suggested_buffer_size=0x%x\n",avi_stream_header.dw_suggested_buffer_size);
    printf("dw_quality=0x%x\n",avi_stream_header.dw_quality);
    printf("dw_sample_size=0x%x\n",avi_stream_header.dw_sample_size);
    printf("left = %d\n",avi_stream_header.rc_frame.left);
    printf("top = %d\n", avi_stream_header.rc_frame.top);
    printf("right = %d\n",avi_stream_header.rc_frame.right) ;
    printf("bottom = %d\n",avi_stream_header.rc_frame.bottom);
    printf("\n");



    uint32_t strf;
    readsize = fread(&strf, 1, sizeof(strf), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(strf)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }

    if (strf != 0x66727473) {
        printf("err %d\n", __LINE__);
        return -1;
    }

    uint32_t strf_size;
    readsize = fread(&strf_size, 1, sizeof(strf_size), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(strf_size)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    printf("strf = 0x%x\n", strf);
    printf("strf size = 0x%x\n", strf_size);
    printf("\n");

    struct BitMapInfo bit_map_info;
    readsize = fread(&bit_map_info, 1, sizeof(bit_map_info), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(bit_map_info)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }

    printf("\nbit map info \n");
    printf("bi_size=0x%x\n",bit_map_info.bit_map_info_header.bi_size);
    printf("bi_width=0x%x\n",bit_map_info.bit_map_info_header.bi_width);
    printf("bi_height=0x%x\n",bit_map_info.bit_map_info_header.bi_height);
    printf("bi_planes=0x%x\n",bit_map_info.bit_map_info_header.bi_planes);
    printf("bi_bit_count=0x%x\n",bit_map_info.bit_map_info_header.bi_bit_count);
    printf("bi_compression=0x%x\n",bit_map_info.bit_map_info_header.bi_compression);
    printf("bi_size_image=0x%x\n",bit_map_info.bit_map_info_header.bi_size_image);
    printf("bi_x_pels_per_meter=0x%x\n",bit_map_info.bit_map_info_header.bi_x_pels_per_meter);
    printf("bi_y_pels_per_mster=0x%x\n",bit_map_info.bit_map_info_header.bi_y_pels_per_mster);
    printf("bi_clr_used=0x%x\n",bit_map_info.bit_map_info_header.bi_clr_used);
    printf("bi_clr_important=0x%x\n",bit_map_info.bit_map_info_header.bi_clr_important);
    printf("\n");

    fpos_t pos;
    int ret = fgetpos(input, &pos);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    //printf("1 pos=%d %x\n", pos,pos);

    uint32_t indx_header;
    readsize = fread(&indx_header, 1, sizeof(indx_header), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(indx_header)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }

    if (indx_header != 0x78646e69) { //indx
        printf("err %d\n", __LINE__);
        return 0;
    }
    printf("indx header 0x%x\n",indx_header);
    ret = fgetpos(input, &pos);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    //printf("2 pos=%d %x\n", pos,pos);
    uint32_t indx_size;
    readsize = fread(&indx_size, 1, sizeof(indx_size), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(indx_size)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    ret = fgetpos(input, &pos);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    //printf("3 pos=%d %x\n", pos,pos);
    printf("indx size 0x%x\n",indx_size);
    printf("indx ....\n");
    
    printf("\n");
    uint8_t *indx = malloc(indx_size + 8);
    if (indx == NULL ) {
        printf("err %d\n", __LINE__);
        return -1;
    }
    readsize = fread(indx + 8, 1, indx_size, input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != indx_size) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    memcpy((void*)indx, (const void*)&indx_header, sizeof(indx_header));
    memcpy((void*)(indx + 4), (const void*)&indx_size, sizeof(indx_size));

    struct AviSuperIndexChunk *avisuperindexchunk;
    avisuperindexchunk = (struct AviSuperIndexChunk *)indx;
    printf("AviSuperIndexChunk %d\n", sizeof(struct AviSuperIndexChunk));
    printf("fcc 0x%x\n",avisuperindexchunk->fcc);
    printf("cd 0x%x\n",avisuperindexchunk->cd);
    printf("w_longs_per_entry 0x%x\n",avisuperindexchunk->w_longs_per_entry);
    printf("b_index_sub_type 0x%x\n",avisuperindexchunk->b_index_sub_type);
    printf("b_index_type 0x%x\n",avisuperindexchunk->b_index_type);
    printf("n_entries_in_use 0x%x\n",avisuperindexchunk->n_entries_in_use);
    printf("dw_chunk_id 0x%x\n",avisuperindexchunk->dw_chunk_id);
    for(int l=0;l<avisuperindexchunk->n_entries_in_use;l++) {
        printf("qw_offset 0x%x\n",avisuperindexchunk->a_index[l].qw_offset);
        printf("dw_size 0x%x\n",avisuperindexchunk->a_index[l].dw_size );
        printf("dw_duration 0x%x\n",avisuperindexchunk->a_index[l].dw_duration);
    }
    printf("\n");
    free(indx);
    ret = fgetpos(input, &pos);
    if (ret < 0) {
        printf("err %d\n", __LINE__);
        return 0;
    }
    //printf("pos=%d %x\n", pos,pos);

    struct ListHeader list_header3;
    readsize = fread(&list_header3, 1, sizeof(list_header3), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(list_header3)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    //list header check
    if (list_header3.list != 0x5453494c) { //LIST
        printf("err %d %x\n", __LINE__,list_header3.list);
        return -1;
    }
    printf("LIST header 0x%x\n", list_header3.list);
    printf("LIST size   0x%x\n", list_header3.list_size);
    printf("LIST ttype  0x%x\n", list_header3.list_ttype);
    printf("\n");

    struct AviStreamHeader avi_stream_header2;
    readsize = fread(&avi_stream_header2, 1, sizeof(avi_stream_header2), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(avi_stream_header2)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    //avi stream header check
    if (avi_stream_header2.fcc != 0x68727473) { //strh
        printf("err %d\n", __LINE__);
        return -1;
    }
    printf("\navi stream header\n");
    printf("fcc=0x%x\n",avi_stream_header2.fcc);
    printf("cb=0x%x\n",avi_stream_header2.cb);
    printf("fcc_type=0x%x\n",avi_stream_header2.fcc_type);
    printf("fcc_header=0x%x\n",avi_stream_header2.fcc_header);
    printf("dw_flag=0x%x\n",avi_stream_header2.dw_flag);
    printf("w_priority=0x%x\n",avi_stream_header2.w_priority);
    printf("w_language=0x%x\n",avi_stream_header2.w_language);
    printf("dw_initial_frames=0x%x\n",avi_stream_header2.dw_initial_frames);
    printf("dw_scale=0x%x\n",avi_stream_header2.dw_scale);
    printf("dw_rate=0x%x\n",avi_stream_header2.dw_rate);
    printf("dw_start=0x%x\n",avi_stream_header2.dw_start);
    printf("dw_length=0x%x\n",avi_stream_header2.dw_length);
    printf("dw_suggested_buffer_size=0x%x\n",avi_stream_header2.dw_suggested_buffer_size);
    printf("dw_quality=0x%x\n",avi_stream_header2.dw_quality);
    printf("dw_sample_size=0x%x\n",avi_stream_header2.dw_sample_size);
    printf("left = %d\n",avi_stream_header2.rc_frame.left);
    printf("top = %d\n", avi_stream_header2.rc_frame.top);
    printf("right = %d\n",avi_stream_header2.rc_frame.right) ;
    printf("bottom = %d\n",avi_stream_header2.rc_frame.bottom);
    printf("\n");

    uint32_t strf2;
    readsize = fread(&strf2, 1, sizeof(strf2), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(strf2)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }

    if (strf2 != 0x66727473) {
        printf("err %d\n", __LINE__);
        return -1;
    }
    printf("strf2 = 0x%x\n", strf2);

    uint32_t strf2_size;
    readsize = fread(&strf2_size, 1, sizeof(strf2_size), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(strf2_size)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    printf("strf2 size = 0x%x\n",strf2_size);
    printf("\n");

    struct WaveFormatX wave_format_x;
    int wave_format_x_size = 18;
    readsize = fread(&wave_format_x, 1, wave_format_x_size, input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != wave_format_x_size) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    printf("w_format_tag 0x%x\n",wave_format_x.w_format_tag);
    printf("n_channels 0x%x\n",wave_format_x.n_channels);
    printf("n_samples_per_sec 0x%x\n",wave_format_x.n_samples_per_sec);
    printf("n_avg_byte_per_sec 0x%x\n",wave_format_x.n_avg_byte_per_sec);
    printf("n_block_align 0x%x\n",wave_format_x.n_block_align);
    printf("w_bits_per_sample 0x%x\n",wave_format_x.w_bits_per_sample);
    printf("cb_size 0x%x\n",wave_format_x.cb_size);
    printf("\n");
    ret = fgetpos(input, &pos);
    printf("pos %x\n", pos);

    uint32_t indx_header2;
    readsize = fread(&indx_header2, 1, sizeof(indx_header2), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(indx_header2)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }

    if (indx_header2 != 0x78646e69) { //indx
        printf("err %d 0x%x\n", __LINE__,indx_header2);
        return 0;
    }
    printf("indx2 header= 0x%x\n", indx_header2);
    uint32_t indx_size2;
    readsize = fread(&indx_size2, 1, sizeof(indx_size2), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(indx_size2)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    printf("indx2 size = 0x%x\n", indx_size2);
    printf("indx2 .....\n");
    printf("\n");

    
    uint8_t *indx2 = malloc(indx_size2+8);
    if (indx2 == NULL ) {
        printf("err %d\n", __LINE__);
        return -1;
    }
    readsize = fread(indx2 + 8, 1, indx_size2, input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != indx_size2) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    memcpy((void*)indx2, (const void*)&indx_header2, sizeof(indx_header2));
    memcpy((void*)(indx2 + 4), (const void*)&indx_size2, sizeof(indx_size2));

    struct AviSuperIndexChunk *avisuperindexchunk2;
    avisuperindexchunk2 = (struct AviSuperIndexChunk *)indx2;
    printf("fcc 0x%x\n",avisuperindexchunk2->fcc);
    printf("cd 0x%x\n",avisuperindexchunk2->cd);
    printf("w_longs_per_entry 0x%x\n",avisuperindexchunk2->w_longs_per_entry);
    printf("b_index_sub_type 0x%x\n",avisuperindexchunk2->b_index_sub_type);
    printf("b_index_type 0x%x\n",avisuperindexchunk2->b_index_type);
    printf("n_entries_in_use 0x%x\n",avisuperindexchunk2->n_entries_in_use);
    printf("dw_chunk_id 0x%x\n",avisuperindexchunk2->dw_chunk_id);
    for(int l=0;l<avisuperindexchunk2->n_entries_in_use;l++) {
        printf("qw_offset 0x%x\n",avisuperindexchunk2->a_index[l].qw_offset);
        printf("dw_size 0x%x\n",avisuperindexchunk2->a_index[l].dw_size );
        printf("dw_duration 0x%x\n",avisuperindexchunk2->a_index[l].dw_duration);
    }
    printf("\n");
    free(indx2);

    int32_t junk;
    readsize = fread(&junk, 1, sizeof(junk), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(junk)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    if (junk != 0x4b4e554a) {
        printf("err %d 0x%x\n", __LINE__, junk);
        return -1;
    }
    printf("junk header = 0x%x\n", junk);
    int32_t junk_size;
    readsize = fread(&junk_size, 1, sizeof(junk_size), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(junk_size)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    printf("junk size = 0x%x\n", junk_size);
    printf("junk ...\n");
    printf("\n");

    uint32_t *junkp = malloc(junk_size);
    if (indx2 == NULL ) {
        printf("err %d\n", __LINE__);
        return -1;
    }
    readsize = fread(junkp, 1, junk_size, input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != junk_size) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    free(junkp);

    ret = fgetpos(input, &pos);
    //printf("pos %x\n", pos);

    struct ListHeader list_header4;
    readsize = fread(&list_header4, 1, sizeof(list_header4), input);
    if (readsize == 0 ) {
        printf("err %d\n", __LINE__);
        return 0;
    } else if (readsize != sizeof(list_header4)) {
        printf("err %d\n", __LINE__);
        return -1;
    } else {
    }
    //list header check
    if (list_header4.list != 0x5453494c) { //LIST
        printf("err %d\n", __LINE__);
        return -1;
    }

    printf("LIST header 0x%x\n", list_header4.list);
    printf("LIST size   0x%x\n", list_header4.list_size);
    printf("LIST ttype  0x%x\n", list_header4.list_ttype);
    printf("\n");
    uint32_t key;
    uint32_t size;
    uint8_t *data;
    for (int i = 0;;i++) {
        ret = fgetpos(input, &pos);
        if (ret < 0) {
            printf("err %d\n", __LINE__);
            return -1;
    
        }
        printf("pos =0x%x ",pos);

        readsize = fread(&key, 1, sizeof(key), input);
        if (readsize == 0 ) {
            printf("end of file %d\n", __LINE__);
            return 0;
        } else if (readsize != sizeof(key)) {
            printf("err %d\n", __LINE__);
            return -1;
        } else {
        }
        char key_char[5];
        memset(key_char,0x0,0x5);
        memcpy((void*)key_char,&key,0x4);
        //printf("key %d %x %s\n",key, key, key_char);
        printf("key %s ", key_char);
        readsize = fread(&size, 1, sizeof(size), input);
        if (readsize == 0 ) {
            printf("err %d\n", __LINE__);
            return 0;
        } else if (readsize != sizeof(size)) {
            printf("err %d\n", __LINE__);
            return -1;
        } else {
        }
        printf("size 0x%x\n",size);
    
        data = malloc(size);
        if (indx2 == NULL ) {
            printf("err %d\n", __LINE__);
            return -1;
        }
        ret = fgetpos(input, &pos);
        if (ret < 0) {
            printf("err %d\n", __LINE__);
            return -1;
    
        }
        //printf("pos =0x%x ",pos);
        readsize = fread(data, 1, size, input);
        if (readsize == 0 ) {
            printf("err %d\n", __LINE__);
            return 0;
        } else if (readsize != size) {
            printf("err %d %d %d\n", __LINE__, size, readsize);
            return -1;
        } else {
        }
        if (key == 0x30307869) {//ix00
             struct AviStdIndex *avistdindex;
             avistdindex = (struct AviStdIndex*)data;
             printf("\n");
             printf("w_longs_per_entry 0x%x\n",avistdindex->w_longs_per_entry);
             printf("b_index_sub_type 0x%x\n",avistdindex->b_index_sub_type);
             printf("b_index_type 0x%x\n",avistdindex->b_index_type);
             printf("n_entries_in_use 0x%x\n",avistdindex->n_entries_in_use);
             printf("dw_chunk_id 0x%x\n",avistdindex->dw_chunk_id);
             printf("qw_base_offset 0x%x\n",avistdindex->qw_base_offset);
             //printf("dw_reserved3 0x%x\n",avistdindex->dw_reserved3);
             printf("\n");
             for(int k=0;k<avistdindex->n_entries_in_use;k++) {
                printf("dw_offset        0x%x\n",avistdindex->a_index[k].dw_offset);
                printf("dw_size          0x%x\n",avistdindex->a_index[k].dw_size);
                if (k > 0) {
                    //printf("diff 0x%x\n", avistdindex->a_index[k].dw_offset - avistdindex->a_index[k-1].dw_offset);

                }
             }
             printf("\n");
        } else if (key == 0x31307869) {//ix01
             struct AviStdIndex *avistdindex;
             avistdindex = (struct AviStdIndex *)data;
             printf("\n");
             printf("w_longs_per_entry 0x%x\n",avistdindex->w_longs_per_entry);
             printf("b_index_sub_type 0x%x\n",avistdindex->b_index_sub_type);
             printf("b_index_type 0x%x\n",avistdindex->b_index_type);
             printf("n_entries_in_use 0x%x\n",avistdindex->n_entries_in_use);
             printf("dw_chunk_id 0x%x\n",avistdindex->dw_chunk_id);
             printf("qw_base_offset 0x%x\n",avistdindex->qw_base_offset);
             //printf("dw_reserved3 0x%x\n",avistdindex->dw_reserved3);
             printf("\n");
             for(int k=0;k<avistdindex->n_entries_in_use;k++) {
                printf("dw_offset        0x%x\n",avistdindex->a_index[k].dw_offset);
                printf("dw_size          0x%x\n",avistdindex->a_index[k].dw_size);
             }
             printf("\n");
        } else if (key == 0x31786469) {//idx1
            int num = size / sizeof(struct AviOldIndexEntry );
            struct AviOldIndexEntry *avi_old_index_entry = (struct AviOldIndexEntry *)data;
            for (int o = 0;o < num;o++) {
                //avi_old_index_entry = (struct AviOldIndexEntry *)(data +  (sizeof(struct AviOldIndexEntry) * o));
                printf("dw_chunk_id 0x%x\n", avi_old_index_entry[o].dw_chunk_id);
                printf("dw_flags 0x%x\n", avi_old_index_entry[o].dw_flags);
                printf("dw_offset 0x%x\n", avi_old_index_entry[o].dw_offset);
                printf("dw_size 0x%x\n", avi_old_index_entry[o].dw_size);
                if (o > 0) {
                    //printf("diff 0x%x\n", avi_old_index_entry[o].dw_offset - avi_old_index_entry[o-1].dw_offset);

                }

            }
        } else if (key == 0x62773130) {//01wb
            ret = fgetpos(input, &pos);
            if (ret < 0) {
                printf("err %d\n", __LINE__);
                return -1;
        
            }
            printf("01wb pos =0x%x ",pos);
            }
        free(data);
        //printf("\n");
    }
    printf("OK\n");
    return  0;

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

	int ret = conv_file(input, output);
	if (ret < 0) {
		printf("ng\n");
	}

	fclose(input);
	fclose(output);
	return 0;
}

