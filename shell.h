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
 * @readfolder: folder to read line input
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
	int (*fun)(pinfo_t *);
} builtin_t;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* shell_err.c */
void eputstr(char *str);
int eputchar_(char c);
int putfdes(char c, int fdes);
int putsfdes(char *str, int fdes);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* ab_str1.c */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
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

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* get_inf.c */
void clr_inf(pinfo_t *inf);
void set_inf(pinfo_t *inf, char **av);
void free_inf(pinfo_t *inf, int all);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

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
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
