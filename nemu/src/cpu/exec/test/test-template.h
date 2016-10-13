#include "cpu/exec/template-start.h"
#include "../flag.h"

#define instr test

static void do_execute() {
	DATA_TYPE result = op_dest->val & op_src->val;
	logical_flag(op_dest->val, op_src->val, result, MSB(result));
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#undef instr

#include "cpu/exec/template-end.h"
