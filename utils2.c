#include "main.h"
#include <stdlib.h>

/**
 * handle_all - handles calling all commands.
 * @cmd: command recieved
 * @av: arg vector
 * @status: exit status of command
 * @p: line pointer to free
 * @p_2: line pointer to free
 * @s: mem to free
 *
 * Return: exit status of command.
 */
int handle_all(char *cmd, char **av, int status, char *p, char *p_2, char **s)
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
		av = create_arg_list(cmd, count);
		if (av == NULL)
			return (status);
		if (_strcmp(av[0], "exit") == 0)
			free(s);
		m_exit(av[0], count, p, p_2, av, temp_s, temp_o);
		builtin_command = check_builtins(av);

		if (builtin_command != NULL)
			status = (*builtin_command)(av);
		if (builtin_command == NULL)
		{
			o = handle_variables_replacement(av, status);
			m = process_alias_command(av);
			status = m ? m : o;

			if (m != 0 && o != 0)
				status = execute_call(av);
		}

		for (j = 0; j < count; j++)
			free(av[j]);
		free(av);
	}
	else
		status = execute_commands(cmd, l);

	free(temp_s);
	free(temp_o);
	return (status);
}
