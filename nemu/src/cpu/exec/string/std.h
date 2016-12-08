#include "cpu/exec/helper.h"
#include "cpu/reg.h"

make_helper(std) {
	print_asm("std");
	cpu.DF = 1;
	return 1;
}

make_helper(cld) {
	print_asm("cld");
	cpu.DF = 0;
	return 1;
}

