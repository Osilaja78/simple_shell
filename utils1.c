#include "main.h"
#include <stdlib.h>

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

	token = _strtok(cmd, delimeter);
	while (token != NULL)
	{
		if (_strcmp(token, "&&") == 0)
			return (1); /* it is an and operator */
		else if (_strcmp(token, "||") == 0)
			return (2); /* it is an or operator */
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
		exit_shell(args[0], count, lineptr, NULL, args);
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
	/*const char *delimeter_1 = "&&", *delimeter_2 = "||";*/
	char **sep, **args, *lineptr;

	lineptr = _strdup(commands);
	if (operators == 1)
	{
		sep = command_separator(lineptr, "&&");
		i = 0;
		while (sep[i] != NULL)
		{
			count = 5;
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
			count = 5;
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
