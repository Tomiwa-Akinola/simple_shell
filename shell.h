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

/* toem_parser.c */
int is_cmd(pinfo_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(pinfo_t *, char *, char *);

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

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* atoi_.c */
int interactive(pinfo_t *inf);
int isdelim_(char c,char *delim);
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

/* toem_environ.c */
char *_getenv(pinfo_t *, const char *);
int _myenv(pinfo_t *);
int _mysetenv(pinfo_t *);
int _myunsetenv(pinfo_t *);
int populate_env_list(pinfo_t *);

/* toem_getenv.c */
char **get_environ(pinfo_t *);
int _unsetenv(pinfo_t *, char *);
int _setenv(pinfo_t *, char *, char *);

/* sh_history.c */
char *gt_file_history(pinfo_t *inf);
int write_hist(pinfo_t *inf);
int rd_hist(pinfo_t *inf);
int bd_hist_list(pinfo_t *inf, char *buf, int lncount);
int renum_hist(pinfo_t *inf);

/* toem_lists.c */
slist_t *add_node(slist_t **, const char *, int);
slist_t *add_node_end(slist_t **, const char *, int);
size_t print_list_str(const slist_t *);
int delete_node_at_index(slist_t **, unsigned int);
void free_list(slist_t **);

/* toem_lists1.c */
size_t list_len(const slist_t *);
char **list_to_strings(slist_t *);
size_t print_list(const slist_t *);
slist_t *node_starts_with(slist_t *, char *, char);
ssize_t get_node_index(slist_t *, slist_t *);

/* toem_vars.c */
int is_chain(pinfo_t *, char *, size_t *);
void check_chain(pinfo_t *, char *, size_t *, size_t, size_t);
int replace_alias(pinfo_t *);
int replace_vars(pinfo_t *);
int replace_string(char **, char *);

#endif
