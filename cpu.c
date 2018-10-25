#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
int registers[16];
int cpsr;//status register

//sets the value of reg to value
void set_reg(int reg, int value){
registers[reg]=value;
}
//returns the value of the register number (int reg)
int get_reg(int reg){
	return registers[reg];
	}
	//returns the contents of cpsr
int get_cpsr(){
	return cpsr;
	}
	//prints out the contents of reg
void show_regs(){
	printf("%s","the value in cpsr is ");
	printf("%d\n",cpsr);
	for(int i =0; i<16; i++){
		printf("%s","R");
		printf("%d",i);
		printf("%s"," == ");
		printf("%d\n",registers[i]);

	}
}



/*
 * does one iteration of fetch-exicute-decode cycle
 * fetches instructions pointed to by reg
 * decodes them (int opcode = inst>>24;)
 * execute (opcode switch statement)
 * 0000 0001 0001 0010 0000
 * b1 = opslitter.two
*/ 
void step(){ //00(command) 00(r0) 00(r1) 00 (r3)
	//unsigned int opcode = registers[PC];
	opsplitter opcode;
	opcode.code = (unsigned int)registers[PC];
	switch(opcode.zero){
		case LDR:
		if(opcode.one ==0){
		printf("%s\n","ERROR NO REGISTER GIVEN");
		}
		break;
		case LDI:
		
		break;
		case LDX:
		
		break;
		case STR: break;
		case ADD:
			
		break;
		case SUB: break;
		case MUL: break;
		case DIV: break;
		case CMP: break;
		case B: break;
		case BEQ: break;
		case BNE: break;
		case BLT: break;
		case BGT: break;
	}
	
}
void step_n(int n){
	for(int i =0; i<n; i++)
	step();
}
