#include "cpu/exec/helper.h"
make_helper(cltd_n);

#define SUFFIX l
#define instr cltd

static void do_execute(){
	if((reg_l(R_EAX) >> 31) & 1) reg_l(R_EDX) = 0xffffffff;
	else reg_l(R_EDX) = 0;
	print_asm("cltd");
}
make_instr_helper(n)

#undef instr
#undef SUFFIX
