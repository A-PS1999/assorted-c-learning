#include "wav-data.h"
#include <stdlib.h>

short *read_input_data(FILE *infile, union wav_header_repr *wav_head) {
    short *data;
    int data_size = wav_head->header.subchunk2_size.int_data;
    short num_channels = wav_head->header.num_channels.short_data;
    short bits_per_sample = wav_head->header.bits_per_sample.short_data;

    if (bits_per_sample != 16) {
        fprintf(stderr, "Error: Samples are not of 16-bit length\n");
        exit(EXIT_FAILURE);
    }

    int bytes_per_sample = bits_per_sample / 8;
    int samples_per_channel = data_size / bytes_per_sample / num_channels;

    if ((data = (short *)malloc(sizeof(samples_per_channel * num_channels * sizeof(short)))) == NULL) {
        fprintf(stderr, "Error: failed to allocate memory for input .wav data\n");
        exit(EXIT_FAILURE);
    }
    
    short *curr = data;
    for (int i=0; i < samples_per_channel; i++) {
        for (int j=0; j < num_channels; j++) {
            if ((fread(curr, bytes_per_sample, 1, infile)) != 1) {
                fprintf(stderr, "Error: failed to read all samples into memory\n");
                exit(EXIT_FAILURE);
            }
            curr++;
        }
    }

    return data;
}

void write_output_wav(FILE *outfile, union wav_header_repr *wav_head, short *input_data, char *outfile_name) {
    printf("Writing to %s...\n", outfile_name);
    fwrite(wav_head, sizeof(union wav_header_repr), 1, outfile);

    int data_size = wav_head->header.subchunk2_size.int_data;
    short num_channels = wav_head->header.num_channels.short_data;
    short bits_per_sample = wav_head->header.bits_per_sample.short_data;
    int bytes_per_sample = bits_per_sample / 8;
    int samples_per_channel = data_size / bytes_per_sample / num_channels;

    fwrite(input_data, sizeof(short), samples_per_channel * num_channels, outfile);
    printf("Successfully wrote data to %s\n", outfile_name);
}