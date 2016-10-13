#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/helper.h"

#define instr jmp

static void do_execute(){
	DATA_TYPE_S disp = op_src->val;
	if(op_src->type == OP_TYPE_REG || op_src->type == OP_TYPE_MEM){
		cpu.eip = disp - concat(decode_rm_, SUFFIX)(cpu.eip + 1) - 1;
		print_asm_template1();
	}
	else{
		cpu.eip += disp;
		print_asm("jmp $0x%x", cpu.eip + 1 + DATA_BYTE);
	}
}

make_instr_helper(i)
#if DATA_BYTE != 1
make_instr_helper(rm)
#endif

#undef instr

#include "cpu/exec/template-end.h"
