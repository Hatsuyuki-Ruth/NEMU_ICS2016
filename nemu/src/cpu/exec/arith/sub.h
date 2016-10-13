#include "cpu/exec/helper.h"
#include "cpu/helper.h"

make_helper(sub_i2a_b);
make_helper(sub_i2rm_b);
make_helper(sub_r2rm_b);
make_helper(sub_rm2r_b);

make_helper(sub_i2a_v);
make_helper(sub_i2rm_v);
make_helper(sub_r2rm_v);
make_helper(sub_rm2r_v);
make_helper(sub_si2rm_v);

#define DATA_BYTE 1
#include "sub_template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sub_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sub_template.h"
#undef DATA_BYTE

make_helper_v(sub_i2a)
make_helper_v(sub_i2rm)
make_helper_v(sub_r2rm)
make_helper_v(sub_rm2r)
make_helper_v(sub_si2rm)
