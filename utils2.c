#include "main.h"
#include <stdlib.h>

/**
 * handle_all - handles calling all commands.
 * @cmd: command recieved
 * @argv: arg vector
 * @status: exit status of command
 * @line: line pointer to free
 * @line_2: line pointer to free
 *
 * Return: exit status of command.
 */
int handle_all(char *cmd, char **argv, int status, char *line, char *line_2)
{
	char *temp_s, *temp_o;
	int count, j, l, m, o;
	int (*builtin_command)(char **);

	temp_s = _strdup(cmd);
	temp_o = _strdup(cmd);
	l = check_logical_operators(temp_o);
	if (l == 0)
	{
		count = count_token(temp_s);
		argv = create_arg_list(cmd, count);
		m_exit(argv[0], count, line, line_2, argv, temp_s, temp_o);
		builtin_command = check_builtins(argv);

		if (builtin_command != NULL)
			status = (*builtin_command)(argv);

		if (builtin_command == NULL)
		{
			o = handle_variables_replacement(argv, status);
			m = process_alias_command(argv);
			status = m ? m : o;

			if (m != 0 && o != 0)
			{
				status = execute_call(argv);
			}
		}

		for (j = 0; j < count; j++)
			free(argv[j]);
		free(argv);
	}
	else
		status = execute_commands(cmd, l);

	free(temp_s);
	free(temp_o);
	return (status);
}
