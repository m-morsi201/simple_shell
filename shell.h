#ifndef SHELL_H
#define SHELL_H

/* for conv_num */
#define CONV_LOWER	1
#define CONV_UNS	2

#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define HIST_FILE ".simple_shell_hist"
#define HIST_MAX 4096

/*define for vrs_func.c*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*define for getinfunc.c*/
#define USE_GETLINE 0
#define USE_STRTOK 0

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>

extern char **envn;

/**
 * struct list_str - it is a singly linked list.
 * @n: it is number.
 * @s: it is a string.
 * @next: points to the next node.
*/

typedef struct list_str
{
	int n;
	char *s;
	struct list_str *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@argco: it is an the argument count.
 *@lnc: the error count
 *@err_num: the error code for exit.
 *@linecount_flag: if on count this line of input
 *@fl_name:it is a filename.
 *@en_v: it is copy of environ.
 *@envn: it is a custom  environ.
 *@his:it is a the history node
 *@alts: the alias node
 *@env_chn: it is changed environ.
 *@stat: the return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@re_fldes: it is a fdes which to read input.
 *@histco: the history line number count
 *@arg: it is a string arguements.
 *@argv: it is an array of strings.
 *@path: it is a path for the current command.
*/

typedef struct passinfo
{
	int env_chn;
	int stat;
	int cmd_buf_type;
	int re_fldes;
	int histco;
	int argco;
	unsigned int lnc;
	int err_num;
	int linecount_flag;
	char *fl_name;
	list_t *en_v;
	list_t *his;
	list_t *alts;
	char **envn;
	char **cmd_buff;
	char *arg;
	char **argv;
	char *path;
} inf_t;

#define INF_IN \
{0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, \
	NULL, NULL, NULL}


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
*/

typedef struct builtin
{
	char *type;
	int (*func)(inf_t *);
} builtin_table;


/* prototypes for str_func.c */
char *str_concat(char *, char *);
char *begin(const char *, const char *);
int str_comp(char *, char *);
int str_leng(char *);

/* prototypes for str_func2.c */
int _putchar(char);
void _puts(char *);
char *str_copy(char *, char *);
char *str_doup(const char *);

/* prototypes for str_func3.c */
char *str_n_copy(char *, char *, int);
char *str_char(char *, char);
char *str_n_concat(char *, char *, int);

/* prototypes for str_func4.c */
char **str_to_wor(char *, char *);
char **str_to_wor2(char *, char);

/* prototypes for memory_fun.c */
char *memo_set(char *, char, unsigned int);
void free_memo(char **);
void *re_allocat(void *, unsigned int, unsigned int);

/* prototypes for free_memory.c */
int ifree_memo(void **);

/* prototypes for more_of_func.c */
int inter_act(inf_t *);
int is_delm(char, char *);
int is_alpha(int);
int str_to_int(char *);

/* prototypes for more_of_func2.c */
int conv_stoint(char *);
void err_mas(inf_t *, char *);
int p_dec(int, int);
char *conv_num(long int, int, int);
void del_comm(char *);

/* prototypes for lis_func.c */
list_t *add_no_fi(list_t **, const char *, int);
list_t *add_no_en(list_t **, const char *, int);
size_t pls(const list_t *);
int dn_ind(list_t **, unsigned int);
void f_list(list_t **);

/* prototypes for lis_func2.c */
size_t ls_length(const list_t *);
char **ls_to_str(list_t *);
size_t pr_ls(const list_t *);
list_t *no_begin(list_t *, char *, char);
ssize_t get_no_ind(list_t *, list_t *);

/* prototypes for std_err_func.c */
void erro_put(char *);
int erro_put_ch(char);
int put_fl_des(char ch, int fl_des);
int ps_fldes(char *s, int fl_des);

/* prototypes for std_err_func2.c */
int erro_at_cmd(char *);
void pr_erro(inf_t *, char *);
int pr_dec(int, int);
char *conv_num(long int, int, int);
void rem_comm(char *);

/* prototypes for inf_func.c */
void clr_inf(inf_t *);
void st_inf(inf_t *, char **);
void fr_inf(inf_t *, int);

/* prototypes for vrs_func.c */
int if_chn(inf_t *, char *, size_t *);
void chk_chn(inf_t *, char *, size_t *, size_t, size_t);
int rep_als(inf_t *);
int rep_vrs(inf_t *);
int rep_str(char **, char *);

/* prototypes for env_fun.c */
char *get_env(inf_t *, const char *);
int my_env(inf_t *);
int my_set_env(inf_t *);
int my_unset_env(inf_t *);
int popu_env_ls(inf_t *);

/* prototypes for env_fun2.c */
char **get_envn(inf_t *);
int unset_envn(inf_t *, char *);
int set_envn(inf_t *, char *, char *);

/* prototypes for get_hist.c */
char *get_histf(inf_t *inf);
int wr_hist(inf_t *inf);
int re_hist(inf_t *inf);
int bld_hist_ls(inf_t *inf, char *buff, int ln_co);
int renum_hist(inf_t *inf);

/* prototypes for cmd_func.c */
int my_ex(inf_t *);
int myo_cd(inf_t *);
int my_hlp(inf_t *);

/* prototypes for myo_his.c */
int my_hist(inf_t *);
int my_als(inf_t *);

/* prototypes for if_cmdfunc.c */
int if_cmd(inf_t *, char *);
char *dup_ch(char *, int, int);
char *f_pth(inf_t *, char *, char *);

/* prototypes for get_lnfunc.c */
ssize_t get_inp(inf_t *);
int get_ln(inf_t *, char **, size_t *);
void sig_hndl(int);

/* prototypes for hsh_func.c */
int hsh(inf_t *, char **);
int fnd_bltin(inf_t *);
void fnd_cmd(inf_t *);
void frk_cmd(inf_t *);

#endif
