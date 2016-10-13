#include "cpu/exec/helper.h"
#include "cpu/helper.h"


make_helper(push_i_b);
make_helper(push_r_v);
make_helper(push_rm_v);
make_helper(push_i_v);

#define DATA_BYTE 1
#include "push_template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "push_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "push_template.h"
#undef DATA_BYTE

make_helper_v(push_r)
make_helper_v(push_rm)
make_helper_v(push_i)

