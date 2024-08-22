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

/*
 *  The Maximum number as a Count this version can work with is : 18446744073709551615
 *  18446744073709551615 BYTE's [Approx 1 EXABYTE]
 */

int main()
{
        unsigned char *in;
       	unsigned long long int len_in_bytes = 18446744073709551615UL;
        
	printf("Length/Count : %llu\n",len_in_bytes);
	printf("\n");

	in = (unsigned char*) malloc(sizeof(unsigned long long int));

/*... STORING from long long int to char array ...*/
	union un obj;
        obj.num = len_in_bytes;
        int bits = Count_Bits(obj.num);
        int bytes = (bits / 8) + !!(bits % 8);
        int size = bytes;
        
	for(int i = size - 1; i >= 0; i--)
        {
                *(in + (size - 1 - i)) = obj.num_arr[i];
        }
/*... END of STORING from long long int to char array ...*/
	

       //Declaration of *out
	unsigned char bits_for_len = Count_Bits(len_in_bytes);
        unsigned char *out;
        out = malloc(sizeof(unsigned char) * ((bits_for_len/8) + 10));

        int count_bit_seq_len = 0;
        
	count_bit_seq_len = Encode(bits_for_len, in, out);
	Decode(out);
       
     	return 0;
}

