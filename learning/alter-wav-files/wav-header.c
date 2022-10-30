#include <stdlib.h>
#include <string.h>
#include "wav-header.h"

void check_header(union wav_header_repr *input_header);

void read_header(FILE *infile, union wav_header_repr *input_header) {
    int i;

    for (i=0; i < WAV_HEADER_SIZE && (input_header->header_arr[i] = getc(infile)) != EOF; i++);

    if (i != WAV_HEADER_SIZE) {
        fprintf(stderr, "Error: .wav header file is incomplete or otherwise could not be completed\n");
        exit(EXIT_FAILURE);
    }

    check_header(input_header);
}

void check_header(union wav_header_repr *input_header) {
    char temp_arr[5];
    temp_arr[4] = '\0';

    if (strcmp(strncpy(temp_arr, input_header->header.chunk_id, 4), "RIFF") != 0) {
        fprintf(stderr, "Error: input file not in RIFF format\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(strncpy(temp_arr, input_header->header.format, 4), "WAVE") != 0) {
        fprintf(stderr, "Error: input file not in WAVE format\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(strncpy(temp_arr, input_header->header.subchunk2_id, 4), "data") != 0) {
        fprintf(stderr, "Error: input .wav file header is not in correct format\n");
        exit(EXIT_FAILURE);
    }
}

void print_header(union wav_header_repr *input_header) {
    printf("Chunk ID: %s\n", input_header->header.chunk_id);
    printf("Chunk size: %d\n", input_header->header.chunk_size.int_data);
    printf("Format: %s\n", input_header->header.format);
    printf("Subchunk 1 ID: %s\n", input_header->header.subchunk1_id);
    printf("Subchunk 1 size: %d\n", input_header->header.subchunk1_size.int_data);
    printf("Audio format: %d\n", input_header->header.audio_format.short_data);
    printf("Number of channels: %d\n", input_header->header.num_channels.short_data);
    printf("Sample rate: %d\n", input_header->header.sample_rate.int_data);
    printf("Byte rate: %d\n", input_header->header.byte_rate.int_data);
    printf("Block align: %d\n", input_header->header.block_align.short_data);
    printf("Bits per sample: %d\n", input_header->header.bits_per_sample.short_data);
    printf("Subchunk 2 ID: %s\n", input_header->header.subchunk2_id);
    printf("Subchunk 2 size: %d\n", input_header->header.subchunk2_size.int_data);
}