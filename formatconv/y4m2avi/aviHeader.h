#ifndef __AVI_HEADER__
#define __AVI_HEADER__


struct RiffHeader {
    uint32_t riff;
    uint32_t file_size;
    uint8_t  data[];
};
struct ListHeader {
    uint32_t list;
    uint32_t list_size;
    uint32_t list_ttype;
    uint8_t list_data[];
};
struct AviMainHeader {
    uint32_t fcc;
    uint32_t cb;
    uint32_t dw_micro_sec_per_frame;
    uint32_t dw_max_bytes_per_sec;
    uint32_t dw_padding_granularity;
    uint32_t dw_flag;
    uint32_t dw_total_frams;
    uint32_t dw_initial_frames;
    uint32_t dw_streams;
    uint32_t dw_suggested_buffer_size;
    uint32_t dw_width;
    uint32_t dw_height;
    uint32_t dw_reserved[4];
};
struct AviStreamHeader {
    uint32_t fcc;
    uint32_t cb;
    uint32_t fcc_type;
    uint32_t fcc_header;
    uint32_t dw_flag;
    uint16_t w_priority;
    uint16_t w_language;
    uint32_t dw_initial_frames;
    uint32_t dw_scale;
    uint32_t dw_rate;
    uint32_t dw_start;
    uint32_t dw_length;
    uint32_t dw_suggested_buffer_size;
    uint32_t dw_quality;
    uint32_t dw_sample_size;
    struct {
        int16_t left;
        int16_t top;
        int16_t right;
        int16_t bottom;
    } rc_frame;
};

struct BitMapInfoHeader  {
    int32_t bi_size;
    int32_t bi_width;
    int32_t bi_height;
    int16_t bi_planes;
    int16_t bi_bit_count;
    int32_t bi_compression;
    int32_t bi_size_image;
    int32_t bi_x_pels_per_meter;
    int32_t bi_y_pels_per_mster;
    int32_t bi_clr_used;
    int32_t bi_clr_important;
};
struct BitMapInfo {
    struct BitMapInfoHeader bit_map_info_header;
//    struct RgbQuad rgb_quad;
};
struct AviSuperIndexChunk {
    int32_t fcc;
    int32_t cd;
    int16_t w_longs_per_entry;
    int8_t b_index_sub_type;
    int8_t b_index_type;
    int32_t n_entries_in_use;
    int32_t dw_chunk_id;
    int32_t dw_reserved[3];
    struct AviSuperIndexEntry {
        int64_t qw_offset;
        int32_t dw_size;
        int32_t dw_duration;
    } a_index[];
};
#define WAVE_FORMAT_X_SIZE (18)
struct WaveFormatX {
    int16_t w_format_tag;
    int16_t n_channels;
    int32_t n_samples_per_sec;
    int32_t n_avg_byte_per_sec;
    int16_t n_block_align;
    int16_t w_bits_per_sample;
    int16_t cb_size;
};

struct AviStdIndex {
    uint16_t w_longs_per_entry;
    uint8_t b_index_sub_type;
    uint8_t b_index_type;
    uint32_t n_entries_in_use;
    uint32_t dw_chunk_id;
    uint64_t qw_base_offset;
    //uint32_t dw_reserved3;
    struct AviStdIndexEntry {
        uint32_t dw_offset;
        uint32_t dw_size;
    } a_index[];
};

struct AviOldIndex {
    uint32_t fcc;
    uint32_t cb;
    struct AviOldIndexEntry {
        uint32_t dw_chunk_id;
        uint32_t dw_flags;
        uint32_t dw_offset;
        uint32_t dw_size;
    }a_index[];
};

#endif
