#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "../flag.h"

#define instr sub

static void do_execute() {
	DATA_TYPE res = op_dest->val - op_src->val;
	cpu.CF = op_dest->val < op_src->val;
	OPERAND_W(op_dest, res);
	arith_flag(op_dest->val, MSB(op_dest->val), (~op_src->val) + 1, MSB((~op_src->val) + 1), res, MSB(res));
	print_asm_template2();
}

#if DATA_BYTE != 1
make_instr_helper(si2rm)
#endif

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#undef instr

#include "cpu/exec/template-end.h"
