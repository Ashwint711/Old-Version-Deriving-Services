#include<stdio.h>
#include<stdlib.h>
#include "encode_utils.c"
#include "decode_utils.c"
#include "utils.c"

union un
{
	unsigned long long int num;
        unsigned char num_arr[sizeof(unsigned long long int)];
};

int main()
{
        unsigned char *in;
       	unsigned long long int len_in_bytes = 11072000;
        
	printf("Length/Count : %llu\n",len_in_bytes);
	printf("\n");

	in = (unsigned char*) malloc(sizeof(unsigned long long int));

	union un obj;
        obj.num = len_in_bytes;
        int bits = Count_Bits(obj.num);
        int bytes = (bits / 8) + !!(bits % 8);
        int size = bytes;
        
	for(int i = size - 1; i >= 0; i--)
        {
                *(in + (size - 1 - i)) = obj.num_arr[i];
        }
	
/*
	unsigned char* ptr = (unsigned char*) &len_in_bytes;
	for(int i = 0; i < 4; i++)
		print_bits(*(ptr + (4 - 1 - i)));	
	printf("\n");
	unsigned char bits_for_len = Count_Bits(len_in_bytes);
	
	unsigned char terminate = ((bits_for_len / 8) + (!!(bits_for_len % 8)));
	unsigned char value,k,remn = 0;
	remn = (bits_for_len % 8);

// for(int i = 0; i < terminate; i++)
//	{
//              *(in + i) = (*(ptr + (terminate - 1 - k)) << (remn > 0 ? 8 - remn : 0)); //removing leading zeros from first byte & also removing leading bit values from next bytes.
//		k += 1;
//		if(k == terminate) break;
//		*(in + i) |= (*(ptr + (terminate - 1 - k)) >> (bits_for_len % 8)); //making space for previously inserted bits in above statement
//	}

	unsigned char byte_index = 0;
	unsigned char bit_index = 0;
	unsigned char bit_count = 0;
	 for (int i = bits_for_len-1; i >= 0; i--) 
	 {
        	int bit = (len_in_bytes >> i) & 1;
        
        	// Place bit into the array at the correct position
        	if (bit) {
            		*(in + byte_index) |= (1 << (7 - bit_index));
        	}
        
        	bit_index++;
        	bit_count++;
        
        	if (bit_index >= 8) {
            		bit_index = 0;
            		byte_index++;
        	}
    	}
	

	
	unsigned char terminator = (bits_for_len / 8) < 1 ? 1 : (bits_for_len / 8);
       */ 
        //Declaration of *out
	unsigned char bits_for_len = Count_Bits(len_in_bytes);
        unsigned char *out;
        out = malloc(sizeof(unsigned char) * ((bits_for_len/8) + 10));

        int count_bit_seq_len = 0;
        
	count_bit_seq_len = Encode(bits_for_len, in, out);
	Decode(out);
       
     	return 0;
}

