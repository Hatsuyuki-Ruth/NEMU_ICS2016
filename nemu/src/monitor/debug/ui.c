#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <elf.h>

extern char *strtab;
extern Elf32_Sym *symtab;
extern int nr_symtab_entry;

void cpu_exec(uint32_t);

typedef struct{
	swaddr_t prev_ebp;
	swaddr_t ret_addr;
}StackFrame;

/* We use the `readline' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args) {
//	volatile int arg_len = strlen(args);
	int arg;
//	printf("%s\n", args);
	if(args != NULL) { sscanf(args, "%d", &arg); }
	else { arg = 1; }
	cpu_exec(arg);
	return 0;
}

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"

static int cmd_info(char *args) {
	if(args == NULL) printf("This command requires exactly one argument.\n");
	if(*args == 'r') {
		int i;
		printf("---GPRs:\n");
		for (i = R_EAX; i <= R_EDI; i++) {
			printf("%%%s: %08d 0x%08x\n", REG_NAME(i), reg_l(i), reg_l(i));
		}
		printf("---PC:\n");
		printf("$eip = %08d 0x%08x\n", cpu.eip, cpu.eip);
		printf("---EFLAGS:\n");
		printf("$EFLAGS = %08d 0x%08x\n", cpu.EFLAGS, cpu.EFLAGS);
		printf("$CF = %d\n", cpu.CF);
		printf("$PF = %d\n", cpu.PF);
		printf("$ZF = %d\n", cpu.ZF);
		printf("$SF = %d\n", cpu.SF);
		printf("$IF = %d\n", cpu.IF);
		printf("$DF = %d\n", cpu.DF);
		printf("$OF = %d\n", cpu.OF);
		printf("--GDTR:\n");
		printf("$GDTR = %08d 0x%08x\n", cpu.GDTR, cpu.GDTR);
		printf("$GDT_LEN = %08d 0x%08x\n", cpu.GDT_LEN, cpu.GDT_LEN);
		printf("--Segmentation:\n");
		printf("$ES = %10d 0x%08x\n", cpu.ES, cpu.ES);
		printf("$CS = %10d 0x%08x\n", cpu.CS, cpu.CS);
		printf("$SS = %10d 0x%08x\n", cpu.SS, cpu.SS);
		printf("$DS = %10d 0x%08x\n", cpu.DS, cpu.DS);
	}
	else if(*args == 'w') {
		traverse();
	}
	else { printf("Invalid argument.\n"); }
	return 0;
}

#include "cpu/exec/template-end.h"
#undef DATA_BYTE

static int cmd_p(char *args) {
	bool successful;
	int res = expr(args, &successful);
	if(!successful) {
		printf("Invalid expression.\n");
		return 0;
	}
	printf("Result: %d 0x%x\n", res, res);
	return 0; 
}

static int cmd_x(char *args) {
	uint32_t num = 0;
	if(args == NULL) {
		printf("Please specify an argument.\n");
		return 0;
	}	
	while(*args != '\0' && *args != ' ') {
		if(*args < '0' || *args > '9') {
			printf("Invalid argument.\n");
			return 0;
		}
		num = num * 10 + (*args - '0');
		args++;
	}
	if(num == 0) {
		printf("Invalid argument.\n");
		return 0;
	}
	if(*args == '\0') {
		printf("Please specify an expression.\n");
		return 0;
	}
	while(*args == ' ') args++;
	bool successful;
	int res = expr(args, &successful);
	if(!successful) {
		printf("Invalid expression.\n");
		return 0;
	}
	uint32_t i = res;
	for(i = res; i < res + num * 4;i += 4) {
		printf("Addr 0x%x: 0x%x\n", i, swaddr_read(i, 4));
	}
	//printf("%d %d\n", res, num);
	return 0;
	
}

static int cmd_w(char *args) {
	bool successful;
	int init_val = expr(args, &successful);
	if(!successful) {
		printf("Invalid expression.\n");
		return 0;
	}
	new_wp(args, init_val);
	return 0;
}

static int cmd_d(char *args) {
	int num = 0;
	if(args) { sscanf(args, "%d", &num); }
	else {
		printf("One argument required.\n");
		return 0;
	}
	free_wp(num);
	return 0;
}

static int cmd_bt(char *args) {
	int i, count = 0;
	StackFrame cur;
	swaddr_t addr = reg_l(R_EBP);
	cur.ret_addr = cpu.eip;
	while(addr){
		printf("#%d: 0x%08x in ", count, cur.ret_addr);
		count++;
		for(i = 0;i < nr_symtab_entry;i++){
			if(symtab[i].st_value <= cur.ret_addr
			&& cur.ret_addr <= symtab[i].st_value + symtab[i].st_size
			&& (symtab[i].st_info & 0xf) == STT_FUNC)
				break;
		}
		printf("%s(", strtab + symtab[i].st_name);
		for(i = 0;i < 4;i++) printf(" %d", swaddr_read(addr + 8 + 4 * i, 4));
		printf(" )\n");
		cur.prev_ebp = swaddr_read(addr, 4);
		cur.ret_addr = swaddr_read(addr + 4, 4);
		addr = cur.prev_ebp;	
	}
	return 0;
}

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si", "Run several steps", cmd_si },
	{ "info", "Print some freaking awesome information about the program", cmd_info },
	{ "p", "Evaluate an expression", cmd_p },
	{ "x", "Print the contents of the RAM", cmd_x },
	{ "w", "Set a watchpoint", cmd_w },
	{ "d", "Delete a watchpoint", cmd_d},
	{ "bt", "Print the stack", cmd_bt}
	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	init_wp_pool();
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}

