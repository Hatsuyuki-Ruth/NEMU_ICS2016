#include "cpu/helper.h"
#include "cpu/exec/helper.h"

make_helper(cmp_i2a_b);
make_helper(cmp_i2a_v);
make_helper(cmp_rm2r_b);
make_helper(cmp_rm2r_v);
make_helper(cmp_r2rm_b);
make_helper(cmp_r2rm_v);
make_helper(cmp_i2rm_b);
make_helper(cmp_i2rm_v);
make_helper(cmp_si2rm_v);

#define DATA_BYTE 1
#include "cmp_template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmp_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmp_template.h"
#undef DATA_BYTE

make_helper_v(cmp_i2a)
make_helper_v(cmp_rm2r)
make_helper_v(cmp_r2rm)
make_helper_v(cmp_i2rm)
make_helper_v(cmp_si2rm)

