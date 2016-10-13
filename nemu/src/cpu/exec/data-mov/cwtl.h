#include "cpu/exec/helper.h"
make_helper(cwtl_n);

#define SUFFIX l
#define instr cwtl

static void do_execute(){
	if((reg_w(R_AX) >> 15) & 1) reg_w(R_DX) = 0xffff;
	else reg_w(R_DX) = 0;
	print_asm("cwtl");
}
make_instr_helper(n)

#undef instr
#undef SUFFIX

