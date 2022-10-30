#include <stdlib.h>
#include <stdio.h>
#include "wav-header.h"
#include "wav-data.h"
#include "wav-type.h"

int main(int argc, char* argv[])
{
    FILE *infile, *outfile;
    union wav_header_repr *wav_head;
    short *input_data;
    double scale_factor;

    if (argc < 3) {
        printf("Usage: alter-wave-vol <input filename> <output_filename> scale-factor\n");
        return 1;
    }

    scale_factor = strtod(argv[3], NULL);

    if ((infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: failed while attempting to open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if ((outfile = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Error: failed to create output file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    if ((wav_head = (union wav_header_repr *)malloc(sizeof(union wav_header_repr))) == NULL) {
        fprintf(stderr, "Error: failed while attempting to allocate memory for .wav header\n");
        exit(EXIT_FAILURE);
    }
    printf("Reading %s header...\n", argv[1]);
    read_header(infile, wav_head);
    print_header(wav_head);

    printf("Reading %s data...\n", argv[1]);
    input_data = read_input_data(infile, wav_head);

    printf("Altering %s by scale factor %f", argv[1], scale_factor);

    write_output_wav(outfile, wav_head, input_data, argv[2]);
    
    fclose(infile);
    fclose(outfile);
    free(wav_head);
    free(input_data);
    return 0;
}