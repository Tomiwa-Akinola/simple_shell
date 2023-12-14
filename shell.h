#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststring - singly linked list
 * @num: number
 * @str: string
 * @next: a pointer to the next node
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} slist_t;

/**
 * struct sendinfo - it contains arguements (pseudo)
 * to pass into a function
 * @arg: arguements from getline
 * @argv: argument vector
 * @path: string path
 * @argc: argument count
 * @ln_count: error count
 * @err_cod: the error code
 * @lncount_flag: counts line of input
 * @filename: program filename
 * @localenv: local copy of environment
 * @environ: modified copy of local environment
 * @history: history node
 * @alias: alias node
 * @localenv_changed: on if local environment is changed
 * @status: return status of the last executed command
 * @cmd_buf: this is the address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: command type ||, &&, ;
 * @readfdes: reads file descriptor
 * @historycount: history line number count
 */
typedef struct sendinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int ln_count;
	int err_cod;
	int lncount_flag;
	char *filename;
	slist_t *localenv;
	slist_t *history;
	slist_t *alias;
	char **environ;
	int localenv_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfdes;
	int historycount;
} pinfo_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(pinfo_t *);
} builtin_t;


/* loop_sh.c */
int mainsh(pinfo_t *inf, char **av);
int fnd_builtin(pinfo_t *inf);
void fnd_cmd(pinfo_t *inf);
void frk_cmd(pinfo_t *inf);

/* sh_pars.c */
int cmd_(pinfo_t *inf, char *path);
char *dupchar_(char *path_str, int stt, int stp);
char *fndpath(pinfo_t *inf, char *path_str, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* shell_err.c */
void eputstr(char *str);
int eputchar_(char c);
int putfdes(char c, int fdes);
int putsfdes(char *str, int fdes);

/* ab_str2.c */
int strlen_(char *s);
int strcmp_(char *s1, char *s2);
char *strchk(const char *string, const char *c);
char *strcat_(char *dest, char *src);

/* ab_str1.c */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _putstr(char *str);
int _putchar(char c);

/* sh_exit.c */
char *strncpy_(char *dest, char *src, int n);
char *strncat_(char *dest, char *src, int n);
char *strchr_(char *str, char c);

/* sh_strtok.c */
char **strtok_(char *str, char *dstr);
char **str_tok(char *str, char dstr);

/* mem_realloc.c */
char *setmem(char *mem, char byt, unsigned int n);
void free_str(char **st);
void *mem_realloc(void *ptr, unsigned int prev_byt, unsigned int new_byt);
int free_ptr(void **ptr);

/* atoi_.c */
int interactive(pinfo_t *inf);
int isdelim_(char c, char *delim);
int isalpha_(int c);
int atoi_(char *s);

/* shell_err1.c */
int err_atoi(char *s);
void print_err(pinfo_t *inf, char *estr);
int print_dec(int input, int fdes);
char *conv_num(long int num, int base, int flags);
void rem_com(char *buf);

/* sh_builtin.c */
int exit_(pinfo_t *inf);
int cd_(pinfo_t *inf);
int help_(pinfo_t *inf);

/* sh_builtin1.c */
int history_(pinfo_t *inf);
int undo_alias(pinfo_t *inf, char *str);
int do_alias(pinfo_t *inf, char *str);
int prt_alias(slist_t *nod);
int alias_(pinfo_t *inf);

/*_getline.c */
ssize_t input_mybuf(pinfo_t *inf, char **buf, size_t *len);
ssize_t get_dinput(pinfo_t *inf);
ssize_t reads_buf(pinfo_t *inf, char *buf, size_t *);
int _getline(pinfo_t *inf, char **ptr, size_t *len);
void sig_inthandler(__attribute__((unused))int sig_num);

/* get_inf.c */
void clr_inf(pinfo_t *inf);
void set_inf(pinfo_t *inf, char **av);
void free_inf(pinfo_t *inf, int all);

/* sh_environ.c */
int env_(pinfo_t *inf);
char *get_env(pinfo_t *inf, const char *c);
int setenv_(pinfo_t *inf);
int unsetenv_(pinfo_t *inf);
int penv_list(pinfo_t *inf);

/* sh_environ2.c */
char **ret_env(pinfo_t *inf);
int unset_env(pinfo_t *inf, char *var);
int set_env(pinfo_t *inf, char *var, char *value);

/* sh_history.c */
char *gt_file_history(pinfo_t *inf);
int write_hist(pinfo_t *inf);
int rd_hist(pinfo_t *inf);
int bd_hist_list(pinfo_t *inf, char *buf, int lncount);
int renum_hist(pinfo_t *inf);

/* sh_list.c */
slist_t *addnode_(slist_t **head, const char *str, int nod);
slist_t *node_end(slist_t **head, const char *str, int nod);
size_t prt_liststr(const slist_t *head);
int del_nod(slist_t **head, unsigned int ind);
void frlist(slist_t **headptr);

/* sh_list1.c */
size_t lslen_(const slist_t *f);
char **ls_tostr(slist_t *f);
size_t prt_list(const slist_t *f);
slist_t *node_stts(slist_t *nod, char *match, char c);
ssize_t gt_nod_ind(slist_t *hd, slist_t *nd);

/* sh_str_alias.c */
int chain_(pinfo_t *inf, char *buf, size_t *ads);
void chk_chain(pinfo_t *inf, char *buf, size_t *ads, size_t a, size_t len);
int rep_alias(pinfo_t *inf);
int rep_var(pinfo_t *inf);
int rep_str(char **oldstr, char *newstr);

#endif
