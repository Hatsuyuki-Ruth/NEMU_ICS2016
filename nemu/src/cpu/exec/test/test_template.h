#include "cpu/exec/helper.h"
#include "cpu/exec/template-start.h"
#include "cpu/decode/modrm.h"
#include "../flag/flag.h"

make_helper(concat(test_r2rm_, SUFFIX)) {
	cpu.OF = 0;
	cpu.CF = 0;
	ModR_M mod;
	DATA_TYPE test1, test2, res;
	Operand op1, op2;
	int addr_len = 1;
	mod.val = instr_fetch(eip + 1, 1);
	if(mod.mod == 0x3) {
		test1 = REG(mod.R_M);
		test2 = REG(mod.reg);
		print_asm("test"str(SUFFIX)" %%%s, %%%s", REG_NAME(mod.R_M), REG_NAME(mod.reg));
	}
	else{
		swaddr_t addr;
		addr_len = read_ModR_M(eip + 1, &op1, &op2);
		addr = op2.addr;
		test1 = MEM_R(addr);
		test2 = REG(mod.reg);
		print_asm("test"str(SUFFIX)" %%%s, *0x%x", REG_NAME(mod.reg), addr);
	}
	res = test1 & test2;
	//printf("%d\n", res);
	logical_flag(test1, test2, res);
	return addr_len + 1;
}

#include "cpu/exec/template-end.h"

