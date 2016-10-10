#define DATA_BYTE 2
#include "push_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "push_template.h"
#undef DATA_BYTE

make_helper(push_r){
	return push_r_l(eip);
}

