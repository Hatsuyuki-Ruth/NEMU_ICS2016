#include "cpu/exec/helper.h"

make_helper(jne_i_b);
make_helper(jne_i_v);

#define DATA_BYTE 1
#include "jne-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jne-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jne-template.h"
#undef DATA_BYTE

make_helper_v(jne_i)
