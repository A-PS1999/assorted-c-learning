#ifndef WAV_TYPE
#define WAV_TYPE

#define WAV_HEADER_SIZE 44

typedef unsigned char byte;

union int_repr {
    int int_data;
    byte int_bytes[4];
};

union short_repr {
    short short_data;
    byte short_bytes[2];
};

struct wav_header {
    char chunk_id[4];
    union int_repr chunk_size;
    char format[4];
    char subchunk1_id[4];
    union int_repr subchunk1_size;
    union short_repr audio_format;
    union short_repr num_channels;
    union int_repr sample_rate;
    union int_repr byte_rate;
    union short_repr block_align;
    union short_repr bits_per_sample;
    char subchunk2_id[4];
    union int_repr subchunk2_size;
};

union wav_header_repr {
    byte header_arr[WAV_HEADER_SIZE];
    struct wav_header header;
};

#endif