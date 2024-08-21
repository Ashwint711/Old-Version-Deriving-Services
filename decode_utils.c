#include<stdio.h>
#include<stdbool.h>
#include "headers.h"

void Decode(unsigned char* arr)
{
	unsigned char val,temp = 0;
	unsigned char cur_bits = 2;
	unsigned char rem_bits = 8;
	unsigned char bits_visited = 0;
	int bit_seq_len = 0;
	int i = 0;

	while(true)
	{
		if( (rem_bits - (cur_bits + 1)) >= 0 )
		{
			val = *(arr + i) >> (8 - (bits_visited + cur_bits));
			val &= (0xff >> (8 - cur_bits));

			temp = *(arr + i);
			temp >>= (8 - ((cur_bits + 1) + bits_visited));

			bits_visited += (cur_bits + 1);
			rem_bits -= (cur_bits + 1);
		}
		else
		{
			val = *(arr + i) << (8 - rem_bits);
			i += 1;
			val |= *(arr + i) >> rem_bits;
			val >>= (8 - cur_bits);

			temp = *(arr + i);
			temp >>= (8 - ((cur_bits + 1) - rem_bits));

			bits_visited = (cur_bits + 1) - rem_bits;
			rem_bits = 8 - bits_visited;
		}
		bit_seq_len += (cur_bits + 1);
		if(temp & 1) break;
		cur_bits = val;
	}
	//	printf("\nLength is stored in next %d bits.\n",val);
	//	printf("Total bits for sequence %d \n\n",bit_seq_len);
	

	// val - Number of bits in which Length/Count is stored.
	// bit_seq_len - Number of bits taken to store sequence of Length/Count.
	
	//TOTAL bits to store whole encoded sequence
	unsigned char total_bits = val + bit_seq_len;
        unsigned char remn = total_bits % 8;//37 % 8 = 5
        int k = (total_bits/8) + !!(total_bits % 8);//4+1
        k -= 1 ;//4
        int size = ((val / 8) + !!(val % 8));//3
        unsigned char value = 0;
        unsigned char *res =  (unsigned char*) calloc(size, sizeof(unsigned char));

        for(int i = (size - 1); i >= 0; i--)//i=2,1,0
        {
                *(res + i) = (*(arr + k) >> (8 - remn));
                k -= 1;
                if(k < 0) break;
                *(res + i) |= (*(arr + k) << remn);
        }

        *(res) &= (0xff >> ((!!(val % 8)) * (8 - (val % 8))));//Don't shift when remainder is 0.


	//printf("Decoded sequence in bits \n");
	unsigned long long int count = 0;
	unsigned char* ptr = (unsigned char*) &count;
	for(i = 0; i < size; i++)
	{
		//print_bits(*(res + i));
                *(ptr + (size - 1 - i)) = *(res + i);
	}
	printf("\n");
	printf("Count is : %llu\n",count);


	
	
	
	
	
	
	
	
	
	
	
	
	
	
/*	unsigned char value = 0;
	unsigned char terminator = 0;
	temp = 0;
	i = bit_seq_len / 8;

	unsigned char rem = (bit_seq_len % 8);
	terminator = (val / 8) < 1 ? 1 : (val) / 8;

	printf("Decoded Sequence \n");
	for(int j = 0; j < terminator; j++)
	{
		value = *(arr + i) << rem;
		i += 1;
		temp = *(arr + i) >> (8 - rem);
		value |= temp;
		//printf("%d ",value);
		print_bits((value>>=(8 - val)));
		value = 0;
		temp = 0;
	
	}
*/
	//val - Total number of bits in which Length is stored.
/*	int size = (val/8) + (!!(val % 8));
	unsigned char *out;
	out = (unsigned char*) calloc(size, sizeof(unsigned char));

	unsigned char one = 1;
	printf("total_bits is : %d\n",total_bits);
	one <<= (8 - (total_bits % 8));
	temp = 0;
	int j,k = 0;
	j = size - 1; //Start storing from last byte of out
	k = (total_bits / 8); //Start scanning from byte where actual length sequence starts
	for(i = 0; i < val; i++)
	{
		temp = (*(arr + k) & one) > 0 ? 1 : 0;
		*(out + j) |= (temp << (i % 8));
		one <<= 1;
		if(one == 0)
		{
			one = 1;
			k -= 1;
		}
		if(k < 0) break;

		if((i + 1) / 8 == 1) j -= 1;
	}

	for(i = 0; i < size; i++){
		print_bits(*(out + i));
	}*/
	printf("\n");
}
