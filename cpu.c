#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memory_system.h"
int registers[16];
int cpsr;//status register LT = 0 GT = 1 EQ = 3

//sets the value of reg to value
void set_reg(int reg, int value){
registers[reg]=value;
printf("the value of register %d is %x\n",reg,registers[reg]);
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
	Word code;
	code.word = memory_fetch_word(registers[PC]);
	//word. = (unsigned int)registers[PC];
	for(int i = 0; i<16; i++){
		//printf("CODE ZERO IS %x\n",code.word);
		if(registers[i]!=0)
		printf("me_R%d = %x\n", i, registers[i]);
	}
	switch(code.zero){
		case LDR:
			registers[code.one]=memory_fetch_word(code.half);//loads with what is add that address
		break;
		case LDI:
			registers[code.one]=code.half;
		break;
		case LDX:
			registers[code.one] = memory_fetch_word(registers[code.three]+code.two);
		break;
		case STR:
			memory_store_word(code.half,registers[code.one]);
		 break;
		case ADD:
			registers[code.one]=registers[code.two]+registers[code.three];
		break;
		case SUB:
			registers[code.one]=(registers[code.two])-(registers[code.three]);
		break;
		case MUL: 
			registers[code.one]=(registers[code.two])*(registers[code.three]);
		break;
		case DIV: 
			registers[code.one]=(registers[code.two])/(registers[code.three]);
		break;
		case CMP:
			if(registers[code.two]>registers[code.three]){
				cpsr = LT;
			}
			else if(registers[code.two]<registers[code.three]){
				cpsr = GT;
			}
			else if(registers[code.two]==registers[code.three]){
				cpsr = LT;
			}
		break;
		case B:
			code.word=code.word<<8;
			registers[PC]=code.word;
		break;
		case BEQ: 
			if(cpsr == Z){
			code.word=code.word<<8;
			registers[PC]=code.word;
		}
		break;
		case BNE:
		if(cpsr != Z){
		code.word=code.word<<8;
		registers[PC]=code.word;
		}
		break;
		case BLT:
		if(cpsr == LT){
			code.word=code.word<<8;
			registers[PC]=code.word;
		}
		break;
		case BGT: 
		if(cpsr == GT){
			code.word=code.word<<8;
			registers[PC]=code.word;
		}
		break;
		printf("EXITIING CASES\n");
	}
	
}
void step_n(int n){
	for(int i =0; i<n; i++)
	step();
}
