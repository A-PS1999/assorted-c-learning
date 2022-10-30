#ifndef WAV_HEADER_H
#define WAV_HEADER_H

#include <stdio.h>
#include "wav-type.h"

void read_header(FILE *infile, union wav_header_repr *input_header);
void print_header(union wav_header_repr *input_header);

#endif