int reg[16];
int cpsr;//status register

//sets the value of reg to value
void set_reg(int reg, int value){
reg[reg]=value;
}
//returns the value of the register number (int reg)
int get_reg(int reg){
	
	}
	//returns the contents of cpsr
int get_cpsr(){
	
	}
	//prints out the contents of reg
void show_regs(){
	
}
/*
 * does one iteration of fetch-exicute-decode cycle
 * fetches instructions pointed to by reg
 * decodes them (int opcode = inst>>24;)
 * execute (opcode switch statement)
*/
void step(){
	
}
void step_n(int n){
	
}
