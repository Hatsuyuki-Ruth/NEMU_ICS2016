#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;
	char *expr;
	int prev_res;
	/* TODO: Add more members if necessary */


} WP;

void init_wp_pool();

void new_wp(char *expr, int init_val);

void free_wp_(WP *wp);

void free_wp(int num);

void traverse();

bool check_watchpoints();

#endif
