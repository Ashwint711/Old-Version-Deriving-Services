#include<stdio.h>
#include<stdlib.h>
#include "encode_utils.c"
#include "decode_utils.c"
#include "utils.c"
#include "IO.c"

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
	unsigned long long int len_in_bytes = 10;

/*... INPUT ...*/

	unsigned long long int *numbers;
	unsigned int count = 0;
	numbers = Input(&count);

/*... Done with INPUT ...*/


/*.. RUNNING INPUT's ..*/
	
	FILE *output;
	output = fopen("output","w");
	if(output == NULL)
	{
		perror("Failed to open Output file!\n");
		return 0;
	}


	for(int i = 0; i < count; i++)
	{
		len_in_bytes = *(numbers + i);

//		printf("Input : %llu\n\n",len_in_bytes);

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
		//out = malloc(sizeof(unsigned char) * ((bits_for_len/8) + 10));
		out = calloc(((bits_for_len/8) + 10), sizeof(unsigned char));

		int count_bit_seq_len = 0;
		//value
		fprintf(output, "Input : %llu\n\n", len_in_bytes);
		//
		count_bit_seq_len = Encode(bits_for_len, in, out);
		//function(fp, out, bits);
		write_bits(output, out, count_bit_seq_len);
		//
		unsigned long long int result = 0;
		result = Decode(out);
		fprintf(output, "Output : %llu\n",result);
		//decoded value
		fprintf(output,"-------------------------------------------\n\n");
	}

	fclose(output);
	return 0;
}

