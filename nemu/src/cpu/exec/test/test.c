#include "cpu/helper.h"
#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "test_template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "test_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "test_template.h"
#undef DATA_BYTE

make_helper(test_r2rm){
	if(ops_decoded.is_operand_size_16) return test_r2rm_w(eip);
	else return test_r2rm_l(eip);
}

