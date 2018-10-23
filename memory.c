#include <stdio.h>
#include "bit_functions.h"

unsigned char mem[32][32];

unsigned char mem_get(unsigned int row_selected, unsigned int col_slected) {
	return mem[bit_find(row_selected)][bit_find(col_slected)];
}
void mem_dump() {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j += 8) {
			printf("0x%04x (0d%04d) 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n",
				i * 32 + j, i * 32 + j,
				mem[i][j], mem[i][j + 1], mem[i][j + 2], mem[i][j + 3], mem[i][j + 4], mem[i][j + 5], mem[i][j + 6], mem[i][j + 7]);
		}
	}
}

void mem_put(unsigned int row_selected, unsigned int col_selected, unsigned char b) {
	mem[bit_find(row_selected)][bit_find(col_selected)]=b;
}
void spit(){
	for(int i =0;i<32;i++){
		for(int j=0;j<32;j++){
		if(j%8==0){
			printf("\n");
		}
			printf("%x",mem[i][j]);
}
}
}

