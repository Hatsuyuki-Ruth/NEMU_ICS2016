#include "cpu/exec/helper.h"

make_helper(jnp_i_b);
make_helper(jnp_i_v);

#define DATA_BYTE 1
#include "jnp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jnp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jnp-template.h"
#undef DATA_BYTE

make_helper_v(jnp_i)
