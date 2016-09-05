#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, DIV, MUL, LEFT_B, RIGHT_B, NEQ, AND, OR, NOT, NUM, NUM16, REG, DEREF
	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},					// plus
	{"==", EQ},						// equal
	{"/", DIV},
	{"-", '-'},
	{"\\*", MUL},
	{"\\(", LEFT_B},
	{"\\)", RIGHT_B},
	{"!=", NEQ},
	{"\\&\\&", AND},
	{"\\|\\|", OR},
	{"!", NOT},
	{"\\$\\w{2,3}", REG},
	{"0[xX][0-9A-Fa-f]+", NUM16},
	{"[0-9]+", NUM}
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

int op_level(int type) {
	switch(type) {
		case OR: return 0;
		case AND: return 1;
		case EQ: return 2;
		case NEQ: return 2; 
		case '+': return 3;
		case '-': return 3;
		case MUL: return 4;
		case DIV: return 4;
		case NOT: return 5;
		case DEREF: return 6;
	}
	return NOTYPE;
}

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[1024];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				//char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				//Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				//position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array `tokens'. For certain types
				 * of tokens, some extra actions should be performed.
				 */
				char tmp = e[position + substr_len];
				e[position + substr_len] = '\0';
				switch(rules[i].token_type) {
					case NUM: strcpy(tokens[nr_token].str, e + position); break;
					case NUM16: strcpy(tokens[nr_token].str, e + position); break;
					case REG: strcpy(tokens[nr_token].str, e + position); break;
					default: tokens[nr_token].str[0] = '\0';
				}
				e[position + substr_len] = tmp;
				tokens[nr_token].type = rules[i].token_type;
				nr_token++;
				position += substr_len;
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
//	for(i = 0; i < nr_token; i++) {
//		printf("%d\n", tokens[i].type);
//		printf("%s\n", tokens[i].str);
//	}
	return true; 
}

int get_int(char *st) {
	int res = 0;
	while(*st != '\0') {
		res = res * 10 + (*st - '0');
		st++;
	}
	return res;
}

int get_int16(char *st) {
	int res = 0;
	while(*st != '\0') {
		int tmp = 0;
		if('0' <= *st && *st <= '9') tmp = *st - '0';
		else if('a' <= *st && *st <= 'f') tmp = *st - 'a' + 10;
		else tmp = *st - 'A' + 10;
		res = res * 16 + tmp;
		st++;
	}
	return res;
}

int get_reg(char *st) {
	if(strcmp(st, "eax") == 0) return reg_l(0);
	if(strcmp(st, "ecx") == 0) return reg_l(1);
	if(strcmp(st, "edx") == 0) return reg_l(2);
	if(strcmp(st, "ebx") == 0) return reg_l(3);
	if(strcmp(st, "esp") == 0) return reg_l(4);
	if(strcmp(st, "ebp") == 0) return reg_l(5);
	if(strcmp(st, "esi") == 0) return reg_l(6);
	if(strcmp(st, "edi") == 0) return reg_l(7);
	if(strcmp(st, "ax") == 0) return reg_w(0);
	if(strcmp(st, "cx") == 0) return reg_w(1);
	if(strcmp(st, "dx") == 0) return reg_w(2);
	if(strcmp(st, "bx") == 0) return reg_w(3);
	if(strcmp(st, "sp") == 0) return reg_w(4);
	if(strcmp(st, "bp") == 0) return reg_w(5);
	if(strcmp(st, "si") == 0) return reg_w(6);
	if(strcmp(st, "di") == 0) return reg_w(7);
	if(strcmp(st, "al") == 0) return reg_b(0);
	if(strcmp(st, "ah") == 0) return reg_b(4);
	if(strcmp(st, "cl") == 0) return reg_b(1);
	if(strcmp(st, "ch") == 0) return reg_b(5);
	if(strcmp(st, "dl") == 0) return reg_b(2);
	if(strcmp(st, "dh") == 0) return reg_b(6);
	if(strcmp(st, "bl") == 0) return reg_b(3);
	if(strcmp(st, "bh") == 0) return reg_b(7);
	return 0;
}

int check_parentheses(int p, int q) {
	return tokens[p].type == LEFT_B && tokens[q].type == RIGHT_B;
}

int eval(int p, int q) {
	while(p < q && tokens[p].type == NOTYPE) p++;
	while(p < q && tokens[q].type == NOTYPE) q--;
//	printf("%d %d\n", p, q);
	if(p > q) { return 0; }
	else if(p == q) {
		if(tokens[p].type == NUM) return get_int(tokens[p].str);
		else if(tokens[p].type == NUM16) return get_int16(tokens[p].str + 2);
		else return get_reg(tokens[p].str + 1);
	}
	else if(check_parentheses(p, q) == true) {
		return eval(p + 1, q - 1);
	}
	else{
		int op = 0, pos, numb = 0, cur_level = NOTYPE;
		for(pos = p; pos <= q; pos++) {
			if(tokens[pos].type == LEFT_B) {
				numb++;
				continue;
			}
			else if(tokens[pos].type == RIGHT_B) {
				numb--;
				continue;
			}
			if(numb || tokens[pos].type == NUM || tokens[pos].type == NUM16 || tokens[pos].type == REG) continue;
			if(cur_level >= op_level(tokens[pos].type)) {
				op = pos;
				cur_level = op_level(tokens[pos].type);
			}
		}
		//printf("OP: %d\n", op);
		switch(tokens[op].type) {
			case '+': return eval(p, op - 1) + eval(op + 1, q);
			case '-': return eval(p, op - 1) - eval(op + 1, q);	
			case MUL: return eval(p, op - 1) * eval(op + 1, q);
			case DIV: return eval(p, op - 1) / eval(op + 1, q);
			case AND: return eval(p, op - 1) && eval(op + 1, q);
			case OR: return eval(p, op - 1) || eval(op + 1, q);
			case EQ: return eval(p, op - 1) == eval(op + 1, q);
			case NEQ: return eval(p, op - 1) != eval(op + 1, q);
			case NOT: return !eval(p + 1, q);
			case DEREF: return *(hw_mem + eval(p + 1, q));
		}
	}
	return 0;
}

int expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	int i, prev = -1;
	for(i = 0; i < nr_token; i++) {
		if(tokens[i].type == MUL && (i == 0 || (tokens[prev].type == NUM || tokens[prev].type == NUM16 || tokens[prev].type == REG))) tokens[i].type = DEREF;
		if(tokens[i].type != NOTYPE) { prev = i; }
	}
	*success = true;
	/* TODO: Insert codes to evaluate the expression. */
	//panic("please implement me");
	return eval(0, nr_token - 1);
}
