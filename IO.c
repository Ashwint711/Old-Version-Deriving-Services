#include<stdio.h>
#include<stdlib.h>
#include "headers.h"

unsigned long long int* Input(unsigned int *count)
{
	unsigned long long int *numbers = NULL;
	unsigned long long int num = 0;
	FILE *fp;
	fp = fopen("tests", "r");
	if(fp == NULL)
	{
		perror("Failed to open file!\n");
		return NULL;
	}
	unsigned int temp_count = 0;
	while(fscanf(fp, "%llu", &num) == 1)
	{
		numbers = (unsigned long long int*) realloc(numbers, sizeof(unsigned long long int) * (temp_count + 1));
		*(numbers + temp_count) = num;
		temp_count += 1;
	}
	*count = temp_count;
	fclose(fp);

	return numbers;
}

void write_bits(FILE *fp, unsigned char *out, int bits)
{
        unsigned char one = 1;
        unsigned char temp = 0;
	int j = 0;
	fprintf(fp, "Encoded Sequence\n");
        for(int i = 0; i < bits; i++)
        {
		j = (i / 8);
		temp = ((*(out + j) & one << (7 - (i % 8))) > 0 ? 1 : 0);
                fprintf(fp, "%d", temp);
        }
        fprintf(fp, "\n\n");
}

