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
#include <stdbool.h>

/*----------for user command chains—-----*/
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3


/*-------forwrite or read buffers space—-- */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1


/*-------MACROS FOR system getline() functions------*/

#define HISTORY_FILE ".shell_history"
#define HISTORY_MAXX 4096
#define CALL_GETLINE 0
#define CALL_STRTOK 0
#define CONV_LOWERCASE 1
#define CONV_UNSIGNED 2

extern char **environ;

/**
 * struct strgList - List all possible singly linked lists
 * @numb: the number of field list
 * @strg: a string literrals
 * @nXtNode: this pointer points to the next adjacent node
 */
typedef struct strgList
{
	int numb;
	char *strg;
	struct strgList *nXtNode;
} list_t;

/**
 *struct pseudo_pass - Incorporates placeholder arguments for passing into a
 *function,enabling a consistent prototype for function pointer structures.
 *@arg: A string literal erived from the getline() function calls,with arg.
 *@argv: An array of strings created from arguments.
 *@path_cmd:A string representing the path for the current command.
 *@arg_count: The count of arguments
 *@line_count: the count of errors
*@history: the node representing the history
 *@alias_node:the node corresponding to alias
 *@modified_env: In the event that 'environ' has been modified.
 *@status: The return status of the most recently executed command.
 *@cmd_buffer: The address of a ptr pointing to 'cmd_buffer,'
 *in the context of command chaining.
 *@cmd_type_buffer: variable handler for command buffer type;
 *@readInput_fd:The file descriptor used to read line input.
 *@count_historyLine:Count of history line (or counter)
 *@exit_error: The error code with calling the exit() function calls.
 *@lineCount_inp: The counting event of the various line of input.
 *@prog_fileName: The program filel’s name.
 *@env:A local copy of the environment variables stored as a linked list.
 *@environ: A customized and modified version of the environment variables
 *derived from a linked list of environment variables.
 */
typedef struct pseudo_pass
{
	char *arg;
	char **argv;
	char *path_cmd;
	int arg_count;
	unsigned int line_count;
	int exit_error;
	int lineCount_inp;
	char *prog_fileName;
	list_t *env;
	list_t *history;
	list_t *alias_node;
	char **environ;
	int modified_env;
	int status;

	char **cmd_buffer;	  /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_type_buffer; /* CMD_type ||, &&, ; */
	int readInput_fd;
	int count_historyLine;
} info_r;

#define INFO_INITIATE                                                \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *struct built_int_strg - Involves an internally implemented
 *string and its associated function.
 *@flag_type: The flag indicating a built-in command.
 *@func: the function
 */
typedef struct built_int_strg
{
	char *flag_type;
	int (*func)(info_r *);
} builtin_table;

/* —-----------parser.c—---------- */
char *cmd_findIn_PATH(info_r *, char *, char *);
int is_exec_cmd(info_r *, char *);
char *char_dupx(char *, int, int);

/*------------shell-loop.c functions—------------- */
int h_sh(info_r *, char **);
int builtin_cmd_find(info_r *);
void find_cmd_PATH(info_r *);
void fork_exec(info_r *);

/* —-------------looph_sh.c—-------------- */
int loophsh(char **);

/*--------------- string.c —-----------------------*/
int strLen(char *);
int lex_StrgCmp(char *, char *);
char *ChkStart_haystk(const char *, const char *);
char *Cat_2Strgs(char *, char *);

/*------------------handling   errors in source codes—-------------- */
void printStrg_input(char *);
int printChar_stderr(char);
int printChar_fd(char c, int fd);
int printInp_strg(char *strg, int fd);



/* —-------------strings handling functions() —-------------------*/
char *copyStrings(char *, char *);
char *strgDuplicate(const char *);
void printsInp_Strg(char *);
int _putchar(char);
char *copyG_strg(char *, char *, int);
char *Strg2cat(char *, char *, int);
char *findChar_inStrg(char *, char);

/* —-----tokenization function calls—---- */
char **SplitStrg_in2(char *, char *);
char **SplitStrg_words(char *, char);
char *mem_constByte(char *, char, unsigned int);
void ss_free(char **);
void *mem_realloc(void *, unsigned int, unsigned int);



/*--------checks and bitwise checks functions()----------*/
int interative_chk(info_r *);
bool chk_Delim(char, const char *);
int verify_alph(int);
int strg_to_int(char *);
int free_ptr(void **);
int convStrg_to_int(char *);
void printError_stdout(info_r *, char *);
int prints_decimal(int, int);
char *similar_itoa(long int, int, int);
void comments_remover(char *);
int exit_shell(info_r *);
int _cd(info_r *);
int myman(info_r *);

/*----------simulation functions—---- */
int _history_list(info_r *);
int sim_alias(info_r *);

/*----------getline() simulations functions calls()------- */
ssize_t getLine_nonLine(info_r *);
int getNxtline_stdin(info_r *, char **, size_t *);
void block_Ctrl_c(int);
void clear_info_r(info_r *);
void set_info_r(info_r *, char **);
void free_info_r(info_r *, int);

/* —-----environ() simulation calls —------ */
char *env_getValue(info_r *, const char *);
int puts_currentenv(info_r *);
int int_envVar(info_r *);
int del_envVar(info_r *);
int populate_envList(info_r *);
char *getHistoryFile(info_r *info);
int appendHistoryFile(info_r *info);
int readHistoryFile(info_r *info);
int addHistoryList(info_r *info, char *buf, int linecount);
int renumbHistoryList(info_r *info);
char **env_strgArray(info_r *);
int del_setenv(info_r *, char *);
int init_setenv(info_r *, char *, char *);

/*-------linked List function calls()---------*/
void free_list(list_t **);
size_t List_length(const list_t *);
char **strg_listSTRUCT(list_t *);
size_t printList_t(const list_t *);
list_t *nodeWith_pfix(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);
list_t *addStartNode(list_t **, const char *, int);
list_t *addStartNode_end(list_t **, const char *, int);
size_t putsStrg_List(const list_t *);
int del_IndexNode(list_t **, unsigned int);
list_t *addEndNode(list_t **head, const char *strg, int numb);


/*-----variable checks functions()------*/
int chk_chainDelim(info_r *, char *, size_t *);
void chk_chainstats(info_r *, char *, size_t *, size_t, size_t);
int aliasReplace(info_r *);
int varReplace(info_r *);
int strgReplace(char **, char *);

#endif	/* end of main.h */

