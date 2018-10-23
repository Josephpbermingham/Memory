#include <stdio.h>
#include "bit_functions.h"
#include "memory.h"
#include "memory_system.h"
int main(int argc, const char* argv[]) {
	printf("start\n");
	//load_memory("read.txt");
	//printf("out of load mem\n entering memory fill\n");
	unsigned char c = 25;
	memory_fill(5,c,7);
	printf("out of mem fill\n");
	mem_dump();
}
