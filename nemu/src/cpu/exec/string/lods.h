#include "cpu/exec/helper.h"

make_helper(lods_n_b);
make_helper(lods_n_v);

#define DATA_BYTE 1
#include "lods-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "lods-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "lods-template.h"
#undef DATA_BYTE

make_helper_v(lods_n)
