#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * check_logical_operators - checks for logical operators in a command.
 * @cmd: command to check
 *
 * Return: 1 if ||, 2 if &&, or 0 if none is found.
 */
int check_logical_operators(char *cmd)
{
	char *token;
	const char *delimeter = " \n";
	char *result;

	token = _strtok(cmd, delimeter);
	while (token != NULL)
	{
		result = _strchr(token, '&');
		if (result != NULL)
		{
			if (*(result + 1) == '&')
				return (1); /* it is an and operator */
		}

		result = _strchr(token, '|');
		if (result != NULL)
		{
			if (*(result + 1) == '|')
				return (2); /* it is an or operator */
		}
		token = _strtok(NULL, delimeter);
	}
	return (0); /* no logical operator found */
}

/**
 * call_execve - calls the execute_call function.
 * @args: commands to execute
 * @count: no of commands
 * @lineptr: memory to be freed
 *
 * Return: exit status of each command.
 */
int call_execve(char **args, int count, char *lineptr)
{
	int status;
	int (*builtin_command)(char **);

	if (args[0] != NULL)
	{
		m_exit(args[0], count, lineptr, NULL, args, NULL, NULL);
		builtin_command = check_builtins(args);
		if (builtin_command != NULL)
			status = (*builtin_command)(args);

		if (builtin_command == NULL)
			status = execute_call(args);
	}
	else
		status = 1;

	return (status);
}

/**
 * execute_commands - execute commands with logical operators.
 * @commands: commands recieved
 * @operators: an int showing which operator
 *
 * Return: nothing.
 */
int execute_commands(char *commands, int operators)
{
	int i, j, exit_status, count;
	char **sep, **args, *lineptr;

	lineptr = _strdup(commands);
	if (operators == 1)
	{
		sep = command_separator(lineptr, "&&");
		i = 0;
		while (sep[i] != NULL)
		{
			count = count_token(sep[i]);
			args = create_arg_list(sep[i], count);

			exit_status = call_execve(args, count, lineptr);
			i++;
			for (j = 0; j < count; j++)
				free(args[j]);
			free(args);
			if (exit_status != 0)
				break;
		}
	}
	else if (operators == 2)
	{
		sep = command_separator(lineptr, "||");
		i = 0;
		while (sep[i] != NULL)
		{
			count = count_token(sep[i]);
			args = create_arg_list(sep[i], count);
			exit_status = call_execve(args, count, lineptr);
			i++;
			for (j = 0; j < count; j++)
				free(args[j]);
			free(args);
			if (exit_status == 0)
				break;
		}
	}
	free(sep);
	free(lineptr);
	return (exit_status);
}

/**
 * handle_variables_replacement - handles variables $? and $$.
 * @argv: args recieved
 * @status: previous command exit status
 *
 * Return: 0 on success, 1 on failure.
 */
int handle_variables_replacement(char **argv, int status)
{
	pid_t pid;

	if (_strcmp(argv[0], "echo") == 0)
	{
		if (argv[1] != NULL && _strchr(argv[1], '$') != NULL)
		{
			if (_strcmp(argv[1], "$?") == 0)
			{
				printf("%i\n", status);
			}
			else if (_strcmp(argv[1], "$$") == 0)
			{
				pid = getpid();
				printf("%d\n", pid);
			}
			else
				printf(" \n");
		}
		else
			return (1);
	}
	else
		return (99);
	return (0);
}

/**
 * file_as_input - handles command from files.
 * @filename: name of file
 * @argv: arguments recieved
 *
 * Return: exit status of executed command.
 */
int file_as_input(char *filename, char **argv)
{
	FILE *file = fopen(filename, "r");
	char command[MAX_COMMAND_LENGTH], **sep;
	size_t length;
	int k, exit_status = 0;

	if (file == NULL)
	{
		perror("Failed to open file");
		return (1);
	}

	while (fgets(command, sizeof(command), file) != NULL)
	{
		/*Remove the newline character from the command*/
		length = _strlen(command);
		if (length > 0 && command[length - 1] == '\n')
		{
			command[length - 1] = '\0';
		}

		/* execute the command */
		sep = command_separator(command, ";");
		k = 0;
		while (sep[k] != NULL)
		{
			exit_status = handle_all(sep[k], argv, exit_status, NULL, NULL, sep);
			k++;
		}
		free(sep);
	}
	fclose(file);
	return (exit_status);
}
