#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "movsx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movsx-template.h"
#undef DATA_BYTE

make_helper_v(movsx_rm2r)

static void do_movsx_b(){
	uint32_t res = (op_src->val << 16) >> 16;
	write_operand_l(op_dest, res);
	print_asm_template2();
}

make_helper(movsx_rm2r_b){
	return idex(eip, decode_rm2r_l, do_movsx_b);
}
