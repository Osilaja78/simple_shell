#include "main.h"
#include <stdlib.h>

/**
 * handle_all_commands - handles calling all commands.
 * @cmd: command recieved
 * @argv: arg vector
 * @exit_status: exit status of command
 * @lineptr: line pointer to free
 * @lineptr_2: line pointer to free
 *
 * Return: exit status of command.
 */
int handle_all_commands(char *cmd, char **argv, int exit_status,\
	char *lineptr, char *lineptr_2)
{
	char *temp_sep, *temp_operator;
	int count, j, l, m, o;
	int (*builtin_command)(char **);

	temp_sep = _strdup(cmd);
	temp_operator = _strdup(cmd);
	l = check_logical_operators(temp_operator);
	if (l == 0)
	{
		count = count_token(temp_sep);
		argv = create_arg_list(cmd, count);
		exit_shell(argv[0], count, lineptr, lineptr_2, argv, temp_sep, \
				temp_operator);
		builtin_command = check_builtins(argv);

		if (builtin_command != NULL)
			exit_status = (*builtin_command)(argv);

		if (builtin_command == NULL)
		{
			o = handle_variables_replacement(argv, exit_status);
			m = process_alias_command(argv);
			exit_status = m ? m : o;

			if (m != 0 && o != 0)
			{
				exit_status = execute_call(argv);
			}
		}

		for (j = 0; j < count; j++)
			free(argv[j]);
		free(argv);
	}
	else
		exit_status = execute_commands(cmd, l);

	free(temp_sep);
	free(temp_operator);
	return (exit_status);
}
