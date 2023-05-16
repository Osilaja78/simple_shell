#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "main.h"
#include <signal.h>

char **create_arg_list(char *tok, int count, char *lineptr, char *lineptr_2);

/**
 * main - Entry point.
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: int.
 */
int main(int argc, char **argv)
{
	char *lineptr = NULL, *lineptr_2 = NULL, *token;
	const char *delimeter = " \n";
	size_t n = 0;
	ssize_t chars_read;
	int count, j, is_interactive = isatty(STDIN_FILENO);
	int exit_status = 0;
	int (*builtin_command)(char **);

	(void)argc;

	/* main loop for the program */
	while (1)
	{
		if (is_interactive) /* cheks if the shell is in interactive mode */
		{
			_putchar('#');
			_putchar(' ');
		}
		fflush(stdout); /* flush the output stream */

		/* get command from standard input */
		chars_read = _getline(&lineptr, &n, stdin);
		if (chars_read == -1)
			return (-1);

		lineptr_2 = _strdup(lineptr);
		token = _strtok(lineptr, delimeter);
		count = 0;
		while (token != NULL)
		{
			count++;
			token = _strtok(NULL, delimeter);
		}
		count++;

		argv = create_arg_list(token, count, lineptr, lineptr_2);
		if (argv[0] != NULL)
		{
			exit_shell(argv[0], count, lineptr, lineptr_2, argv);
			builtin_command = check_builtins(argv);
			if (builtin_command != NULL)
				exit_status = (*builtin_command)(argv);

			exit_status = execute_call(argv);
		}

		for (j = 0; j < count; j++)
			free(argv[j]);
		free(argv);
		if (lineptr != NULL)
			free(lineptr);
		free(lineptr_2);
		if (!is_interactive)
			return (exit_status);
	}
	free(lineptr_2);
	return (0);
}

/**
 * create_arg_list - creates a list of args for execve.
 * @tok: token passed from main
 * @count: no of arguments passed
 * @lineptr: pointer passed from main
 * @lineptr_2: pointer copy passed from main
 *
 * Return: list of arguments.
 */
char **create_arg_list(char *tok, int count, char *lineptr, char *lineptr_2)
{
	char **av;
	const char *delimeter = " \n";
	int i;

	av = malloc(sizeof(char *) * count);
	if (av == NULL)
	{
		perror("Failed to allocate memory\n");
		free(lineptr_2);
		free(lineptr);
		return (NULL);
	}

	tok = _strtok(lineptr_2, delimeter);
	for (i = 0; tok != NULL; i++)
	{
		av[i] = _strdup(tok);
		tok = _strtok(NULL, delimeter);
	}

	av[i] = NULL;
	return (av);
}
