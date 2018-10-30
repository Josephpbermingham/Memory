#include <stdio.h>
#include "bit_functions.h"
#include "memory.h"
#include "memory_system.h"
#include "cpu.h"
int main(int argc, const char* argv[]) {
	opsplitter test;
	test.code = 0xffaa3344;
	
	
Word w;
w.word = 0xffaabbcc;
printf("%x\n%x\n%x\n%x\n%x\n%x\n%x\n", w.word, w.int3,w.half,w.zero,w.one,w.two,w.three);
w.word=w.word<<8;
printf("%x\n",w.int3);

}
