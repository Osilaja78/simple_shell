#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "main.h"
#include <signal.h>

char **create_arg_list(char *tok, int count);
int count_token(char *token);

/**
 * main - Entry point.
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: int.
 */
int main(int argc, char **argv)
{
	char *lineptr = NULL, *lineptr_2 = NULL, *token, **sep;
	const char *delimeter = "\n";
	size_t n = 0;
	ssize_t chars_read;
	int k, is_interactive = isatty(STDIN_FILENO);
	int status = 0;
	char *filename;

	if (argc == 2)
	{
		filename = argv[1];
		status = file_as_input(filename, argv);
		return (status);
	}

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

		token = _strtow(lineptr, delimeter); /* separate by newline */
		while (token != NULL)
		{
			lineptr_2 = _strdup(token);
			sep = command_separator(token, ";");
			k = 0;
			while (sep[k] != NULL)
			{
				status = handle_all(sep[k], argv, status, lineptr, lineptr_2);
				k++;
			}
			free(sep);
			token = _strtow(NULL, delimeter);
		}

		if (lineptr != NULL)
			free(lineptr);
		free(lineptr_2);
		if (!is_interactive)
			return (status);
	}
	free(lineptr_2);
	return (0);
}

/**
 * count_token - counts a token.
 * @token: token to count
 *
 * Return: number of token.
 */
int count_token(char *token)
{
	int count;
	char *tok;
	const char *delimeter = " \n";

	tok = _strtok(token, delimeter);
	count = 0;
	while (tok != NULL)
	{
		if (_strchr(tok, '#') != NULL)
			break;
		count++;
		tok = _strtok(NULL, delimeter);
	}
	count++;
	return (count);
}

/**
 * create_arg_list - creates an argument list.
 * @tok: token recieved
 * @count: no. of tokens to allocate memory for
 *
 * Return: list of arguments.
 */
char **create_arg_list(char *tok, int count)
{
	char *command, **av, *token;
	const char *delimeter = " \n";
	int i;

	command = tok;
	av = malloc(sizeof(char *) * count); /* allocate the memory */
	if (av == NULL)
		return (NULL);

	/**
	 * tokenize the command (by space) and store
	 * each command in the allocated memory
	 */
	token = _strtok(command, delimeter);
	for (i = 0; token != NULL; i++)
	{
		if (_strchr(token, '#') != NULL)
			break;

		av[i] = _strdup(token);
		token = _strtok(NULL, delimeter);
	}

	av[i] = NULL;
	return (av);
}
