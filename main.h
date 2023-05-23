#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

/* ----- Prototype for utility functions ----- */

int execute_call(char **argv);
char *get_file_path(char *cmd);
int builtin_env(void);
void exit_shell(char *cmd, int count, char *l_ptr, char *l_ptr_2, char **argv);
void print_env(char *cmd);
extern char **environ;
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **command_separator(char *line, char *delimiter);
char **create_arg_list(char *tok, int count);
int check_logical_operators(char *cmd);
int execute_commands(char *commands, int operators);
int call_execve(char **args, int count, char *lineptr);

/* ----- Prototype for string functions ----- */

char *_strtok(char *str, const char *delim);
char *_strtow(char *str, const char *delim);
char *_strchr(const char *str, int c);
char *_strdup(char *str);
int _strlen(char *str);
char *_strcat(char *src, const char *dest);
char *_strcpy(char *dest, const char *src);
int _putchar(char c);
int _strcmp(const char *str1, const char *str2);

/* ----------- BUILTINS --------------- */
/**
 * struct _builtins - struct for builtins
 * @name: name of builtin
 * @fn: corresponding function
 *
 * Description: contains struct for builtins.
 */
typedef struct _builtins
{
	char *name;
	int (*fn)(char **args);
} _builtins;

int _setenv(char **args);
int _unsetenv(char **args);
int _cd(char **args);
int (*check_builtins(char **args))(char **);

/* ------------- ALIASES -------------- */
#define MAX_ALIASES 100  /* Maximum number of aliases */
#define MAX_ALIAS_NAME 50  /* Maximum length of an alias name */
#define MAX_ALIAS_VALUE 100  /* Maximum length of an alias value */

/**
 * struct Alias - sruct for aliases.
 * @name: name of the alias
 * @value: valu3 of the alias
 *
 * Description: contains struct for aliases.
 */
typedef struct Alias
{
	char name[MAX_ALIAS_NAME];
	char value[MAX_ALIAS_VALUE];
} Alias;

void print_aliases(void);
void print_alias(char *name);
void define_alias(char *name, char *value);
int process_alias_command(char **args);


#endif
