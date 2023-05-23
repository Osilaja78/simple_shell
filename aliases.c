#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Alias aliases[MAX_ALIASES];  /* Array to store aliases */
int num_aliases = 0;  /* Number of aliases currently defined */

/**
 * print_aliases - prints all aliases
 *
 * Return: nothing.
 */
void print_aliases(void)
{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		printf("%s=%s\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * print_alias - prints a single alias.
 * @name: name of alias to print
 *
 * Return: nothing.
 */
void print_alias(char *name)
{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		if (_strcmp(name, aliases[i].name) == 0)
		{
			printf("%s=%s\n", aliases[i].name, aliases[i].value);
			return;
		}
	}
}

/**
 * define_alias - defines an alias.
 * @name: name of alias
 * @value: value of alias
 *
 * Return: nothing.
 */
void define_alias(char *name, char *value)
{
	int i;

	/* Check if the alias already exists */
	for (i = 0; i < num_aliases; i++)
	{
		if (_strcmp(name, aliases[i].name) == 0)
		{
			/* Replace the value of the existing alias */
			_strcpy(aliases[i].value, value);
			return;
		}
	}

	/* Check if the maximum number of aliases has been reached */
	if (num_aliases >= MAX_ALIASES)
	{
		fprintf(stderr, "Maximum number of aliases reached\n");
		return;
	}

	/* Add a new alias */
	_strcpy(aliases[num_aliases].name, name);
	_strcpy(aliases[num_aliases].value, value);
	num_aliases++;
}

/**
 * process_alias_command - main function to handle aliases.
 * @args: argunets recieved from stdin
 *
 * Return: 0 on success, and 1 on failure.
 */
int process_alias_command(char **args)
{
	int i;
	char *name, *value, *result;

	if (_strcmp(args[0], "alias") == 0)
	{
		if (args[1] == NULL)
			print_aliases(); /* print all aliases if no args */
		else if (args[2] == NULL)
		{
			/* One argument, print the specified alias */
			print_alias(args[1]);
		}
		else
		{
			result = malloc(sizeof(char) * 10);
			strcpy(result, "");
			for (i = 1; args[i] != NULL; i++)
			{
				strcat(result, args[i]);
				strcat(result, " ");
			}
			name = _strtok(result, "=");
			value = _strtok(NULL, "=");

			if (value == NULL)
			{
				/* No value provided, print the specified alias */
				print_alias(name);
			}
			else
			{
				/* Define or redefine the alias */
				define_alias(name, value);
			}
		}
	}
	else
		return (1);
	free(result);
	return (0);
}
