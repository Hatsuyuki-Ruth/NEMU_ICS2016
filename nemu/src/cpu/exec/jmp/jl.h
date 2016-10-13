#include "cpu/exec/helper.h"

make_helper(jl_i_b);
make_helper(jl_i_v);

#define DATA_BYTE 1
#include "jl-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jl-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jl-template.h"
#undef DATA_BYTE

make_helper_v(jl_i)
