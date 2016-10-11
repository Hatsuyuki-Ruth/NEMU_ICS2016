#include "nemu.h"
#include "cpu/exec/helper.h"

void update_SF(int msbdes) {
	cpu.SF = msbdes;
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

void update_CF(int src1, int msbsrc1, int src2, int msbsrc2, int des, int msbdes, int op) {
	cpu.CF = (msbsrc1 & msbsrc2) | ((msbsrc1 | msbsrc2) & (~msbdes));
	cpu.CF ^= op;
}

void logical_flag(int src1, int src2, int des, int msbdes) {
	update_ZF(des);
	update_SF(msbdes);
	update_PF(des);
}


