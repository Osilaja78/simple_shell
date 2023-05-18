#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * check_builtins - checks if command is a builtin.
 * @args: command to be checked
 *
 * Return: a pointer to the builtin function
 * (if command is a builtin), else NULL
*/
int (*check_builtins(char **args))(char **)
{
	int i;
	_builtins builtins[] = {
		{"setenv", &_setenv},
		{"unsetenv", &_unsetenv},
		{"cd", &_cd},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].name != NULL; i++)
	{
		if (_strcmp(builtins[i].name, args[0]) == 0)
			return (builtins[i].fn);
	}
	return (NULL);
}

/**
 * _setenv - sets an environment variable.
 * @args: variable and value to set
 *
 * Return: on success 0, 1 on failure.
*/
int _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		fprintf(stderr, "Error: unable to set environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * _unsetenv - unsets an environment variable.
 * @args: env variable to unset
 *
 * Return: 0 on success, 1 on failure.
*/
int _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (unsetenv(args[1]) != 0)
	{
		fprintf(stderr, "Error: unable to unset environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * _cd - changes current working directory.
 * @args: command line arguments
 *
 * Return: 0 on success, 1 on failure.
 */
int _cd(char **args)
{
	char *dir;
	char cwd[4096];

	if (args[1] == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			fprintf(stderr, "cd: No $HOME variable set\n");
			return (1);
		}
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		dir = getenv("OLDPWD");
		if (dir == NULL)
			return (1);
	}
	else
		dir = args[1];

	if (chdir(dir) != 0)
	{
		fprintf(stderr, "./hsh: 1: cd: can't cd to %s", dir);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL || setenv("PWD", cwd, 1) != 0)
	{
		perror("cd");
		return (1);
	}
	if (setenv("OLDPWD", getenv("PWD"), 1) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
