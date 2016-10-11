#ifndef _FLAG_H
#define _FLAG_H

#include "nemu.h"
#include "cpu/exec/helper.h"

void update_SF(int des) {
	cpu.SF = MSB(des);
}

void update_ZF(int des) {
	cpu.ZF = (des == 0);
}

void update_PF(int des) {
	int sum = 0, i;
	for(i = 0;i < 8;i++) {
		sum += (des & 1);
		des >>= 1;
	}
	cpu.PF = !(sum & 1);
}

void update_CF(int src1, int src2, int des, int op) {
	cpu.CF = (MSB(src1) & MSB(src2)) | ((MSB(src1) | MSB(src2)) & (~MSB(des)));
	cpu.CF ^= op;
}

void logical_flag(int src1, int src2, int des) {
	update_ZF(des);
	update_SF(des);
	update_PF(des);
}

#endif

