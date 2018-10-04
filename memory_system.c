#include <stdio.h>
#include "memory_system.h"
#include "memory.h"
#include "decoder.h"

void split_address(int address, unsigned char *lower, unsigned char *upper) {
	*lower = address & DECODER_BITMASK;
	*upper = (address & DECODER_BITMASK << DECODER_SHIFTER)) >> DECODER_SHIFTER;
}
void memory_store(int address, unsigned char value) {
	unsigned char lower, upper;
	split address(address, &lower, upper, &upper);
	mem_put(decoder(lower), decoder(upper), value);
}
unsigned char memory_fetch(int address) {
	unsigned char lower, upper;
	split_address(address, &lower, &upper);
	return(mem_get(upper, lower));

}
unsigned int memory_fetch_word(int address) {
	
}
void memory_store_word(int address, unsigned int value) {

}
/*
run memory add on some file 
first line is address
next lines are 32 bit quantitys
*/
void load_memory(char *filename) {
	int address;
	FILE *file;
	char buff[4];
	file = fopen(filename, "r");
	int i = 0;
	while (fgets(line, sizeof line, file) != NULL) {
		if (i == 0) {
			address = line;
		}
		else {
			memory_store(address,line)
			printf(stderr,"%d,%d",address,line)//TODO: testing block, test then remove 
		}
		i++;
	}

	fscanf(file, "0x%08", buff);//how do i choose an address
	memory_store(address,buff);
}
void memory_fill(int start_address, unsigned char value, int num_bytes) {
	unsigned int x = start_address / 32;
	unsigned int x start_address % 32; 
	for (int i = 0; i < num_bytes; i++) {
		mem_put(x, y, value);
	}
}