
#include <stdio.h>
#include <stdlib.h>
#include "memory_system.h"
#include "memory.h"
#include "decoder.h"

typedef union{
	unsigned int word;
	struct{
		unsigned char zero;
		unsigned char one;
		unsigned char two;
		unsigned char three;
	};
}Word;
void split_address(int address, unsigned char *lower, unsigned char *upper) {
	*lower = address & DECODER_BITMASK;
	*upper = (address & DECODER_BITMASK << (DECODER_SHIFTER)) >> DECODER_SHIFTER;
}

void memory_store(int address, unsigned char value) {
	unsigned char lower, upper;
	split_address(address, &lower,&upper);
	printf("%d, %u, %u\n",address, lower,upper);
	mem_put(decoder(upper), decoder(lower), value);//THIS WAS THE ISSUE I NEEDED TO SWAP LOWER AND UPPER
}
unsigned char memory_fetch(int address) {
	unsigned char lower, upper;
	split_address(address, &lower, &upper);
	return(mem_get(upper, lower));//TODO check if this is correct

}
/*
 * gets four bytes 
 */
unsigned int memory_fetch_word(int address) {
	Word getWord;
	getWord.word = memory_fetch(address);
	return getWord.word;
}
/* 
 * 4 bytes
 */
void memory_store_word(int address, unsigned int value) {
	Word w;
	w.word = value;
	memory_store(address+3, w.zero);
	memory_store(address + 2, w.one);
	memory_store(address + 1, w.two);
	memory_store(address, w.three);
}
/*
run memory add on some file 
first line is address
next lines are 32 bit quantitys
*/
void load_memory(char *filename) {
	printf("the start of load mem\n");
	int address;
	FILE *file;
	char line[4];//this is four vecause 255 + null term
	int linear;//this is the variable used to convert to unsigned chars from whatever i am getting from the file
	file = fopen(filename, "r");
	int i = 0;
	while (fgets(line, sizeof line, file) != NULL) {
		
		if (i == 0) {
			address = (atoi(line)); 
		}
		else {
			linear = atoi(line);
			memory_store((address+i-1),linear);
			printf("%d,%d\n",(address+i-1),(unsigned char)linear);
		}
		i++;
		}
	}

	
/*
 * This function should fill memory, but what it is doing is adding it by +1 +1, not +0 +1.
 */
void memory_fill(int start_address, unsigned char value, int num_bytes) {
//	unsigned int x = start_address / 32;
//  unsigned int y = start_address % 32; 
	for (int i = 0; i < num_bytes; i++) {
		//printf("%d, %d ,%u\n", x,y,value);
		memory_store(start_address+i,value);
		//mem_put(x, y, value);
	}
}
