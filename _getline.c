#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 1024
void sighandler(int signum);
static char *buffer;

/**
 * _getline - works like the getline funcion.
 * @lineptr: pointer to buffer where string is stored
 * @n: no of characters read
 * @stream: stdin
 *
 * Return: no. of characters read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	/*static char *buffer = NULL;*/
	ssize_t total_size = 0, buffer_size = BUFFER_SIZE;
	int bytes_read;

	if (lineptr == NULL || !n || !stream)
		return (-1);

	buffer = malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (-1);

	bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	signal(SIGINT, sighandler);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (-1);
	}

	total_size = bytes_read;
	if (total_size >= buffer_size)
	{
		buffer_size += BUFFER_SIZE;
		buffer = realloc(buffer, buffer_size);
		if (buffer == NULL)
			return (-1);
	}

	buffer[total_size] = '\0';
	*n = total_size;
	*lineptr =  buffer;
	return (total_size);
}

/**
 * sighandler - signal handler.
 * @signum: signal number
 *
 * Rerturn: Nothing.
 */
void sighandler(int signum)
{
	(void)signum;
	_putchar('\n');
	free(buffer);
	exit(1);
}
