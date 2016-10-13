#include "cpu/exec/helper.h"

make_helper(leave_n_v);

#define DATA_BYTE 2
#include "leave-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "leave-template.h"
#undef DATA_BYTE

make_helper_v(leave_n)
