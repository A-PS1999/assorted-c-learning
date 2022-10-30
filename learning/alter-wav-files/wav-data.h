#ifndef WAV_DATA_H
#define WAV_DATA_H

#include <stdio.h>
#include "wav-type.h"

short *read_input_data(FILE *infile, union wav_header_repr *wav_head);
void write_output_wav(FILE *outfile, union wav_header_repr *wav_head, short *input_data, char *outfile_name);

#endif