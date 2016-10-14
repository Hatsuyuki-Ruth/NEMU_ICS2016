#include "cpu/exec/helper.h"

make_helper(stos_n_b);
make_helper(stos_n_v);

#define DATA_BYTE 1
#include "stos-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "stos-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "stos-template.h"
#undef DATA_BYTE

make_helper_v(stos_n)
