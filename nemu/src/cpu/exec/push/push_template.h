#include "cpu/exec/helper.h"
#include "cpu/exec/template-start.h"
#include "cpu/decode/modrm.h"

make_helper(concat(push_r_, SUFFIX)){
	int num_reg = instr_fetch(cpu.eip, 1) & 7;
	cpu.esp -= DATA_BYTE;
	swaddr_write(cpu.esp, DATA_BYTE, REG(num_reg));
	return 1;
}

#include "cpu/exec/template-end.h"
	
