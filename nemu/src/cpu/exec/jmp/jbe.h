#include "cpu/exec/helper.h"

make_helper(jbe_i_b);
make_helper(jbe_i_v);

#define DATA_BYTE 1
#include "jbe-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jbe-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jbe-template.h"
#undef DATA_BYTE

make_helper_v(jbe_i)
