#ifndef ENCODE_DECODE_H

#define ENCODE_DECODE_H

int Encode(unsigned char len, unsigned char* in, unsigned char* out);

unsigned long long int Decode(unsigned char* arr);

void print_bits(unsigned char value);

void write_bits(FILE *fp, unsigned char* output, int out);

unsigned long long int* Input(unsigned int *count);

#endif
