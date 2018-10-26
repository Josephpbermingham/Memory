#include <stdio.h>
#include "bit_functions.h"
#include "memory.h"
#include "memory_system.h"
#include "cpu.h"
int main(int argc, const char* argv[]) {
	opsplitter test;
	test.code = 0xffaa3344;
	printf("%x\n",test.zero);
	printf("%x\n",test.one);
	printf("%x\n",test.hold.two);
	printf("%x\n",test.hold.three);

}
