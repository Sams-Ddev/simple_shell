#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

/*--------------for read/write buffers—------------*/
#define READ_BUFFER_SIZE 1024
#define BUFFER_FLUSH1
#define WRITE_BUFFER_SIZE 1024

/* —------for convert_number()------------------- */
#define CONVT_LOWERCASE       1
#define CONVT_UNSIGNED        2
#define USE_GETLINE 0
#define USE_STRTOK 0

/*------------for command chains Handling—-----------*/
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

#define FILE_HISTORY       ".shell_history"
#define MAX_HISTORY        4096

extern char **environ;


/**
 * struct linkdList - a  singly linked list struct
 * @num: the number field
 * @strng: a string literals
 * @next: points to the next node
 */
typedef struct linkdList
{
        int num;
        char *strng;
        struct linkdList *next;
} list_t;

/**
 *struct passArg_info - contains  a huge list of pseudo-arguements to pass into a function,
 *              allowing a formerd, uniform prototype for function pointer struct
 *@arg: the string literals generated from getline() mfunctions containing arguements
 *@argv: the array of string literals generated from arg.
 *@path: a strings path for the current working command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history nodes of the shell
 *@alias: the alias node of the shell
 *@env_changed: on if environ was changed
 *@status: the return status of the last executed shell command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passArg_info
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
        int cmd_buf_type; /* CMD_type ||, &&, ; */
        int readfd;
        int histcount;
} info_t;


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_Table;

/* —------------shell_loop functions —------------*/
int mainLoop(info_t *, char **);
int findBuiltinCmd(info_t *);
void findCmdInPATH(info_t *);
void forkExec(info_t *);
int isExeCmd(info_t *, char *);
char *charDuplicate(char *, int, int);
char *findCmdPATHstrg(info_t *, char *, char *);
int loop_hsh(char **);

/*------------errors handlers-------------- */
void putsInputStr(char *);
int writeCharError(char);
int writeCharFd(char c, int fd);
int writeInpstrng(char *strng, int fd);

/* —--------Strings manipulations—------------ */
int strngLen(char *);
int stringCompr(char *, char *);
char *IshaystackStart(const char *, const char *);
char *CatStrngs(char *, char *);
char *CopyStrng(char *, char *);
char *DupStrngs(const char *);
void _puts(char *);
char *copyStrng(char *, char *, int);
char *StrngCat(char *, char *, int);
int _putchar(char);
char *charLocator(char *, char);

/*-------stgrings splitting func()----------- */
char **splitsStrng(char *, char *);
char **splitsStrng2(char *, char);

/*-------memory management—---- */
char *_memset(char *, char, unsigned int);
void freeStrngs(char **);
void *_realloc(void *, unsigned int, unsigned int);
int freePointers(void **);

/* toemstrng2Int.c */
int interactiveMode(info_t *);
int charDelimCheck(char, char *);
int AlphabetCheck(int);
int strng2Int(char *);

int _erratoi(char *);
void puts_error(info_t *, char *);
int puts_decimal(int, int);
char *clone_itoa(long int, int, int);
void removeComment(char *);

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

int _myhistory(info_t *);
int _myalias(info_t *);
ssize_t getNoNewline(info_t *);
int _getline(info_t *, char **, size_t *);
void ctrlC_Handler(int);

/* toem_getinfo.c */
void Init_Info(info_t *);
void set_Info(info_t *, char **);
void free_Info(info_t *, int);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populateEnvList(info_t *);

char **getEnviron(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *getHistory(info_t *info);
int writeHistory(info_t *info);
int read_history(info_t *info);
int buildHistory(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

list_t *add_node(list_t **, const char *, int);
list_t *addNodeAtEnd(list_t **, const char *, int);
size_t printListStrng(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **listArrayStrngs(list_t *);
size_t printListElements(const list_t *);
list_t *nodeWithPrefix(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

int chainDelimCk(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replacesAlias(info_t *);
int replaceVars(info_t *);
int replaceStrngs(char **, char *);

#endif /* main.h */
