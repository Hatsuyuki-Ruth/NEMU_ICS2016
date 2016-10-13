#include "cpu/exec/helper.h"

make_helper(test_i2a_b);
make_helper(test_i2rm_b);
make_helper(test_r2rm_b);


make_helper(test_i2a_v);
make_helper(test_i2rm_v);
make_helper(test_r2rm_v);

#define DATA_BYTE 1
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "test-template.h"
#undef DATA_BYTE

make_helper_v(test_i2a)
make_helper_v(test_i2rm)
make_helper_v(test_r2rm)
