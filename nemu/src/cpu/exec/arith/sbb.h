#include "cpu/exec/helper.h"

make_helper(sbb_i2a_b);
make_helper(sbb_i2rm_b);
make_helper(sbb_r2rm_b);
make_helper(sbb_rm2r_b);

make_helper(sbb_i2a_v);
make_helper(sbb_i2rm_v);
make_helper(sbb_r2rm_v);
make_helper(sbb_rm2r_v);
make_helper(sbb_si2rm_v);

#define DATA_BYTE 1
#include "sbb_template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sbb_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sbb_template.h"
#undef DATA_BYTE

make_helper_v(sbb_i2a)
make_helper_v(sbb_i2rm)
make_helper_v(sbb_r2rm)
make_helper_v(sbb_rm2r)
make_helper_v(sbb_si2rm)
