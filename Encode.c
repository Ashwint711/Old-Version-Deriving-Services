#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
unsigned char Count_Bits(int e)
{
	unsigned char bits = 0;
	while(e != 0)
	{
		bits += 1;
		e >>= 1;
	}

	return bits;
}

int Encode(int len, unsigned char *in, unsigned char *out)
{
	unsigned char bits_for_len = 0;
	bits_for_len = Count_Bits(len);// 40-> 6 bits
	
/*.... Creating Array of Lengths ....*/

	unsigned char *lengths_arr;
	lengths_arr = (unsigned char*) malloc(sizeof(unsigned char) * 4);
	
	unsigned char val = bits_for_len;
	unsigned char bit_cnt = 0;
	int count = 0;
	while(true)
	{
		bit_cnt = 0;
		*(lengths_arr + count) = val;
		
		while(val != 0)
		{
			bit_cnt += 1;
			val >>= 1;
		}
		
		val = bit_cnt;
		count += 1;
		if(bit_cnt <= 2) break;

	}


	//Reverse lengths_arr
	for(int i = 0; i < (count/2); i++)
	{
		val = *(lengths_arr + i);
		*(lengths_arr + i) = *(lengths_arr + (count - i - 1));
		*(lengths_arr + (count - i - 1)) = val;
	}
/*.... END OF Array of Lengths Creation....*/



/*.... Combining Lengths as a single bit sequence in *Out ....*/
	unsigned char value = 0;
	unsigned char bits = 0;
	unsigned char rem_bits = 8;
	unsigned int total_bits = 0;

	unsigned char* temp_out = out;

	for(int i = 0; i < count; i++)//Iterating through all elements of Lengths_arr
	{
		value = *(lengths_arr + i);
		bits = Count_Bits(value);

		if( (rem_bits - (bits + 1)) > 0)
		{
			value <<= (rem_bits - bits);
			*temp_out |= value;

			rem_bits -= (bits + 1);
		}
		else if((rem_bits - (bits + 1)) < 0)
		{
			value >>= (bits - rem_bits);
			*temp_out |= value;

			value = *(lengths_arr + i);
			value <<= (8 - (bits - rem_bits));
			*(temp_out += 1) |= value;

			rem_bits = (8 - (bits - rem_bits)) - 1;
		}
		else
		{
			*temp_out |= value;
		}

		total_bits += (bits + 1);
	}

	*(out + (total_bits / 8)) |= (1 << (8 - (total_bits % 8)));
	
/*.... END OF Combining Lengths as a single bit sequence in *Out ....*/


/*.... Appending *in data in *out after length sequence ....*/
	temp_out = out;
	out += (total_bits / 8) + (!!(total_bits % 8));
	for(int i = 0; i < len; i++)
	{
		*(out + i) = *(in + i);
	}

	
	printf("Printing values of Bytes containing sequence bits : \n");
	for(int i = 0; i < (total_bits / 8) + (!!(total_bits % 8)); i++)
	{
		printf("%d\n",*(temp_out+i));
	}

/*.... END Of Appending *in data in *out after length sequence ....*/
}

int main()
{
	unsigned char *in;
	int len = 1048576;//alphabets in CAPs and small
	in = (unsigned char*) malloc(sizeof(unsigned char) * len);
	
	for(int i = 0; i < len; i++)
		*(in+i) = (0xf + i);

	//Declaration of *out
	unsigned char *out;
	out = malloc(sizeof(unsigned char) * (len + 10));


	int count_bit_seq_len = 0;
	count_bit_seq_len = Encode(len, in, out);
	return 0;
}
