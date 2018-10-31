
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
	//printf("%d, %u, %u\n",address, lower,upper);
	memory_put(decoder(upper), decoder(lower), value);//THIS WAS THE ISSUE I NEEDED TO SWAP LOWER AND UPPER
}
unsigned char memory_fetch(int address) {
	unsigned char lower, upper;
	split_address(address, &lower, &upper);
	return memory_get(decoder(upper), decoder(lower));//TODO check if this is correct

}
/*
 * gets four bytes 
 */
unsigned int memory_fetch_word(int address) {
	Word getWord;
	getWord.zero = memory_fetch(address);
	getWord.one = memory_fetch(address + 1);
	getWord.two = memory_fetch(address + 2);
	getWord.three = memory_fetch(address + 3);
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
	int address;
	FILE *file;
	int linear;
	file = fopen(filename, "r");
	int i = 0;
	fscanf(file, "0x%x", &address);
	while (1) {	
		if(fscanf(file, "%x", &linear) == EOF){
			break;
		}
		else {
			memory_store_word(address,linear);
			address += 4;
		}
		i++;
	}
	fclose(file);
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
