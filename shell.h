#ifndef SHELL_H
#define SHELL_H
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *Aname;
/* Global history counter */
int Ahist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @Adir: A directory path.
 * @Anext: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *Adir;
	struct list_s *Anext;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @Aname: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *Aname;
	int (*f)(char **Aargv, char **Afront);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @Aname: The name of the alias.
 * @Avalue: The value of the alias.
 * @Anext: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *Aname;
	char *Avalue;
	struct alias_s *Anext;
} alias_t;

/* Global aliases linked list */
alias_t *Aaliases;

/* Main Helpers */
ssize_t _getline(char **Alineptr, size_t *n, FILE *Astream);
void *_realloc(void *Aptr, unsigned int Aold_size, unsigned int Anew_size);
char **_strtok(char *Aline, char *Adelim);
char *get_location(char *Acommand);
list_t *get_path_dir(char *Apath);
int execute(char **Aargs, char **Afront);
void free_list(list_t *Ahead);
char *_itoa(int num);

/* Input Helpers */
void handle_line(char **Aline, ssize_t Aread);
void variable_replacement(char **Aargs, int *Aexe_ret);
char *get_args(char *Aline, int *Aexe_ret);
int call_args(char **Aargs, char **Afront, int *Aexe_ret);
int run_args(char **Aargs, char **Afront, int *Aexe_ret);
int handle_args(int *Aexe_ret);
int check_args(char **Aargs);
void free_args(char **Aargs, char **Afront);
char **replace_aliases(char **Aargs);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *Adest, const char *Asrc);
char *_strncat(char *Adest, const char *Asrc, size_t n);
char *_strcpy(char *Adest, const char *Asrc);
char *_strchr(char *s, char c);
int _strspn(char *s, char *Aaccept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *Acommand))(char **Aargs, char **Afront);
int shellby_exit(char **Aargs, char **Afront);
int shellby_env(char **Aargs, char __attribute__((__unused__)) **Afront);
int shellby_setenv(char **Aargs, char __attribute__((__unused__)) **Afront);
int shellby_unsetenv(char **Aargs, char __attribute__((__unused__)) **Afront);
int shellby_cd(char **Aargs, char __attribute__((__unused__)) **Afront);
int shellby_alias(char **Aargs, char __attribute__((__unused__)) **Afront);
int shellby_help(char **Aargs, char __attribute__((__unused__)) **Afront);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *Avar);

/* Error Handling */
int create_error(char **Aargs, int Aerr);
char *error_env(char **Aargs);
char *error_1(char **Aargs);
char *error_2_exit(char **Aargs);
char *error_2_cd(char **Aargs);
char *error_2_syntax(char **Aargs);
char *error_126(char **Aargs);
char *error_127(char **Aargs);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **Ahead, char *Aname, char *Avalue);
void free_alias_list(alias_t *Ahead);
list_t *add_node_end(list_t **Ahead, char *Adir);
void free_list(list_t *Ahead);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_commands(char *Afile_path, int *Aexe_ret);
#endif
