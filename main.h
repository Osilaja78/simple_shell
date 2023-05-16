#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

int execute_call(char **argv);
char *get_file_path(char *cmd);
int builtin_env(void);
void exit_shell(char *cmd, int count, char *l_ptr, char *l_ptr_2, char **argv);
void print_env(char *cmd);
extern char **environ;
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* Prototype for string functions */
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
 * @func: corresponding function
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
int (*check_builtins(char **args))(char **);

#endif
