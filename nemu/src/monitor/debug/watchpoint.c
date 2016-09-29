#include "monitor/watchpoint.h"
#include "monitor/expr.h"
#include "string.h"
#include "malloc.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		//wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

void new_wp(char *expr, int init_val) {
	if (free_ == NULL) {
		printf("No enough space for watchpoints.\n");
		return;
	}
	WP* cur = free_;
	free_ = free_->next;
	cur->next = head;
	cur->expr = (char *)malloc(strlen(expr) + 1);
	strcpy(cur->expr, expr);
	cur->prev_res = init_val;
	head = cur;
}

void free_wp_(WP *wp) {
	free(wp->expr);
	wp->next = free_;
	//wp->NO = free_->NO + 1;
	free_ = wp;
}

void free_wp(int num) {
	//printf("%d\n", num);
	WP *cur = head, *prev = head;
	int i;
	for (i = 0;i < num;i++) {
		//printf("%d\n", cur - wp_pool);
		if(cur == NULL) {
			printf("Argument out of bound.\n");
			return;
		}
		//printf("%d\n", cur - wp_pool);
		cur = cur->next;
		//printf("%d\n", cur - wp_pool);
	}
	//printf("%d\n", cur - wp_pool);
	if(cur == NULL) {
		printf("Argument out of bound.\n");
		return;
	}
	for (i = 0;i < num - 1;i++) prev = prev->next;
	if(cur == head) prev = NULL;
	//printf("Freeing\n");
	//printf("%d %d %d\n", cur - wp_pool, prev - wp_pool, head - wp_pool);
	if(prev != NULL) { prev->next = cur->next; }
	else { head = head->next; }
	free_wp_(cur);
}

void traverse() {
	int cnt = 0;
	WP *cur = head;
	if (head != NULL) { printf("Head at address $%d.\n", head - wp_pool); }
	else { printf("No watchpoints.\n"); }
	while (cur != NULL) {
		printf("Watchpoint #%d: %s = %d, at address $%d, pointing to $%d.\n", cnt, cur->expr, cur->prev_res, cur - wp_pool, cur->next - wp_pool);
		cur = cur->next;
		cnt++;
	}
}

bool check_watchpoints() {
	int cnt = 0;
	bool flag = 0;
	WP *cur = head;
	while (cur != NULL){
		bool successful;
		int cur_res = expr(cur->expr, &successful);
		if(cur->prev_res != cur_res) {
			printf("Watchpoint #%d triggered. The value of the expression %s changed from %d to %d.\n", cnt, cur->expr, cur->prev_res, cur_res);
			cur->prev_res = cur_res;
			flag = 1;
		}
		cur = cur->next;
		cnt++;
	}
	return flag;
}

