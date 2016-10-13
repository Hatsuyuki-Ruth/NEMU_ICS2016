#include "cpu/exec/helper.h"
#include "cpu/helper.h"

make_helper(pop_r);

#define DATA_BYTE 2
#include "pop_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "pop_template.h"
#undef DATA_BYTE

//make_helper_v(pop_rm)
make_helper_v(pop_r)
