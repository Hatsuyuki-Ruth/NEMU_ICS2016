#define DATA_BYTE 2
#include "push_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "push_template.h"
#undef DATA_BYTE

char suffix;

make_helper(push_r){
	if(suffix == 'l') return push_r_l(eip);
	else return push_r_w(eip);
}

