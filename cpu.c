#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memory_system.h"
int registers[16];
int cpsr;//status register LT = 0 GT = 1 EQ = 3

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
		printf("%x\n",registers[i]);

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
	switch(code.three){
		case LDR:
			set_reg(code.two, memory_fetch_word(code.zero + (code.one << 8)));
		break;
		case LDI:
			set_reg(code.two, code.zero + (code.one << 8));
		break;
		case LDX:
			registers[code.two] = memory_fetch_word(registers[code.zero]+code.one);
		break;
		case STR:
			memory_store_word(code.zero + (code.one << 8),registers[code.two]);
		 break;
		case ADD:
			set_reg(code.two, registers[code.one] + registers[code.zero]);
		break;
		case SUB:
			set_reg(code.two, registers[code.one] - registers[code.zero]);
		break;
		case MUL: 
			set_reg(code.two, registers[code.one] * registers[code.zero]);
		break;
		case DIV: 
			set_reg(code.two, registers[code.one] / registers[code.zero]);
		break;
		case CMP:
			if(registers[code.one]>registers[code.zero]){
				cpsr = LT;
			}
			else if(registers[code.one]<registers[code.zero]){
				cpsr = GT;
			}
			else if(registers[code.one]==registers[code.zero]){
				cpsr = Z;
			}
		break;
		case B:
			code.word=code.word>>8;
			registers[PC] = code.word - 4;
		break;
		case BEQ: 
			if(cpsr == Z){
				code.word=code.word>>8;
				registers[PC] = code.word - 4;
			}
		break;
		case BNE:
			if(cpsr != Z){
				code.word=code.word>>8;
				registers[PC] = code.word - 4;
			}
		break;
		case BLT:
			if(cpsr == LT){
				code.word=code.word>>8;
				registers[PC] = code.word - 4;
			}
		break;
		case BGT: 
			if(cpsr == GT){
				code.word=code.word>>8;
				registers[PC] = code.word - 4;
			}
		break;
		case AND:
			set_reg(code.two, registers[code.one] & registers[code.zero]);
			break;
		case ORR:
			set_reg(code.two, registers[code.one] | registers[code.zero]);
			break;
		case EOR:
			set_reg(code.two, registers[code.one] ^ registers[code.zero]);
			break;
		case BLE:
			if(cpsr == LT || cpsr == Z){
				code.word=code.word>>8;
				registers[PC] = code.word - 4;
			}
			break;
		case BGE:
			if(cpsr == GT || cpsr == Z){
				code.word=code.word>>8;
				registers[PC] = code.word - 4;
			}
			break;
		case BL:
			registers[LR] = registers[PC] + 4;
			registers[PC] = code.word=code.word>>8;
			registers[PC] = code.word - 4;
			break;
		}
		
	registers[PC] += 4;
}
void step_n(int n){
	for(int i =0; i<n; i++)
	step();
}
