#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute(){
	DATA_TYPE res = op_dest->val - op_src->val;
	cpu.CF = op_dest->val < op_src->val;
	arith_flag(op_dest->val, MSB(op_dest->val), ~op_src->val, MSB(~op_src->val), res, MSB(res));
	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#undef instr

#include "cpu/exec/template-end.h"
