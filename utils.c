#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_ARGS 100

/**
 * execute_call - Executes an execve() call.
 * @argv: argument vector passed
 *
 * Return: Nothing.
 */
int execute_call(char **argv)
{
	char *cmd = NULL, *actual_cmd = NULL;
	pid_t pid;
	int status;

	cmd = argv[0];
	if (cmd == NULL)
		return (-1);

	print_env(cmd);
	replace_var(argv);
	actual_cmd = get_file_path(cmd);

	if (actual_cmd == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
		free(actual_cmd);
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(actual_cmd, argv, NULL);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("Error during fork...");
	else
	{
		waitpid(pid, &status, 0);
		if (actual_cmd != cmd)
			free(actual_cmd);

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		else
			return (1);
	}
	return (0);
}

/**
 * get_file_path - Gets the path of a command.
 * @cmd: command passed
 *
 * Return: path to file.
 */
char *get_file_path(char *cmd)
{
	char *path, *path_cpy, *file_path, *p_token;
	int cmd_len, dir_len;
	struct stat buffer;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_cpy = _strdup(path);
	cmd_len = _strlen(cmd);
	p_token = _strtok(path_cpy, ":");
	while (p_token != NULL)
	{
		dir_len = _strlen(p_token);
		file_path = malloc(cmd_len + dir_len + 2);
		_strcpy(file_path, p_token);
		_strcat(file_path, "/");
		_strcat(file_path, cmd);
		_strcat(file_path, "\0");

		if (stat(file_path, &buffer) == 0)
		{
			free(path_cpy);
			return (file_path);
		}
		else
		{
			free(file_path);
			p_token = _strtok(NULL, ":");
		}
	}
	if (stat(cmd, &buffer) == 0)
	{
		free(path_cpy);
		return (cmd);
	}
	if (path_cpy != NULL)
		free(path_cpy);
	return (NULL);
}

/**
 * m_exit - Exits the shell.
 * @cmd: command passed
 * @c: count passed
 * @l: buffer to free
 * @l_2: buffer to free
 * @av: arg list to free
 * @t: mem to free
 * @o: mem to free
 *
 * Return: Nothing.
 */
void m_exit(char *cmd, int c, char *l, char *l_2, char **av, char *t, char *o)
{
	int j, status = 0;

	if (_strcmp(cmd, "exit") == 0)
	{
		if (c > 2)
			status = atoi(av[1]);

		for (j = 0; j < c; j++)
			free(av[j]);
		free(av);
		free(l);
		free(l_2);
		free(t);
		free(o);
		exit(status);
		return;
	}
	else
		return;
}

/**
 * print_env - Prints out environment variables.
 * @cmd: command passed.
 *
 * Return: Nothing.
 */
void print_env(char *cmd)
{
	char **env_var = environ;

	if (_strcmp(cmd, "env") == 0)
	{
		while (*env_var != NULL)
		{
			printf("%s\n", *env_var);
			env_var++;
		}
		return;
	}
}

/**
 * command_separator - handles command separator ;
 * @line: command recieved
 * @delimiter: separator
 *
 * Return: an array of commands.
 */
char **command_separator(char *line, char *delimiter)
{
	char **commands;
	char *token =  NULL;
	int i;

	commands = malloc(MAX_ARGS * sizeof(char *));
	if (!commands)
		return (NULL);

	token = _strtok(line, delimiter);
	for (i = 0; token != NULL; i++)
	{
		commands[i] = token;
		token = _strtok(NULL, delimiter);
	}

	commands[i] = NULL;

	return (commands);
}
