#include<stdio.h>
#include<stdbool.h>
#include "headers.h"

unsigned long long int Decode(unsigned char* arr)
{
	unsigned char val,temp = 0;
	unsigned char cur_bits = 2;
	unsigned char rem_bits = 8;
	unsigned char bits_visited = 0;
	int bit_seq_len = 0;
	int i = 0;

/*... FETCHING count of Bits in which Count/Length is stored. ...*/

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

/*... END of FETCHING count of Bits in which Count/Length is stored. ...*/
	
	/* val - Number of bits in which Length/Count is stored. */
	/* bit_seq_len - Number of bits taken to store sequence of Length/Count. */

/*... DECODING actual COUNT/LENGTH ...*/

	//TOTAL bits to store whole encoded sequence
	unsigned char total_bits = val + bit_seq_len;
	unsigned char remn = total_bits % 8;
	int k = (total_bits/8) + !!(total_bits % 8);
	k -= 1 ;
	int size = ((val / 8) + !!(val % 8));
	unsigned char value = 0;
	unsigned char *res =  (unsigned char*) calloc(size, sizeof(unsigned char));

	for(int i = (size - 1); i >= 0; i--)
	{
		if(remn > 0)
		{
			*(res + i) = (*(arr + k) >> (8 - remn));
			k -= 1;
			if(k < 0) break;
			*(res + i) |= (*(arr + k) << remn);
		}
		else
		{
			*(res + i) = *(arr + k);
			k -= 1;
		}
	}

	*(res) &= (0xff >> ((!!(val % 8)) * (8 - (val % 8))));//Don't shift when remainder is 0.

/*... END of FETCHING actual COUNT/LENGTH ...*/


/*... DECODED SEQUENCE to Number...*/

	unsigned long long int count = 0;
	unsigned char* ptr = (unsigned char*) &count;
	for(i = 0; i < size; i++)
	{
		*(ptr + (size - 1 - i)) = *(res + i);
	}

/*... END ...*/

	return count;
}
