#include "cpu/exec/helper.h"
#include "cpu/helper.h"

make_helper(ret_n_v);
make_helper(ret_i_v);

#define DATA_BYTE 2
#include "ret_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ret_template.h"
#undef DATA_BYTE

make_helper_v(ret_n)
make_helper_v(ret_i)
