#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _strtok - tokenizes a string.
 * @str: string to tokenize
 * @delim: delimeter
 *
 * Return: tokenized string.
 */
char *_strtok(char *str, const char *delim)
{
	static char *last_token;
	char *token = NULL;

	if (str == NULL && last_token == NULL)
		return (NULL);

	if (str != NULL)
	{
		last_token = str;
	}

	while (*last_token && _strchr(delim, *last_token))
	{
		last_token++;
	}

	if (*last_token == '\0')
	{
		return (NULL);
	}

	token = last_token;

	while (*last_token && !_strchr(delim, *last_token))
	{
		last_token++;
	}

	if (*last_token != '\0')
	{
		*last_token++ = '\0';
	}

	return (token);
}

/**
 * _strtow - splits the string by newline character.
 * @str: string to tokenize
 * @delim: delimeter (newline)
 *
 * Return: tokenized string.
 */
char *_strtow(char *str, const char *delim)
{
	static char *last_token;
	char *token = NULL;

	if (str == NULL && last_token == NULL)
		return (NULL);

	if (str != NULL)
	{
		last_token = str;
	}

	while (*last_token && _strchr(delim, *last_token))
	{
		last_token++;
	}

	if (*last_token == '\0')
	{
		return (NULL);
	}

	token = last_token;

	while (*last_token && !_strchr(delim, *last_token))
	{
		last_token++;
	}

	if (*last_token != '\0')
	{
		*last_token++ = '\0';
	}

	return (token);
}

/**
 * _strchr - searches a string for a char.
 * @str: string to be searched
 * @c: character to search for
 *
 * Return: str.
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}

/**
 * _strdup - Entry point.
 * @str: string to be copied.
 *
 * Description: copies a given string to an allocated memory.
 *
 * Return: pointer to copied string.
 */
char *_strdup(char *str)
{
	int i;
	int str_len = 0;
	char *string;

	if (str == NULL)
	{
		return (NULL);
	}

	while (str[str_len] != '\0')
	{
		str_len++;
	}

	string = malloc((str_len + 1) * sizeof(char));

	if (string == NULL)
	{
		return (NULL);
	}

	for (i = 0; i <= str_len; i++)
	{
		string[i] = str[i];
	}
	return (string);
}

/**
 * _strcat - Entry point.
 * @src: source
 * @dest: destination
 *
 * Description: Concatenates two strings.
 *
 * Return: Alwats 0
 */
char *_strcat(char *src, const char *dest)
{
	char *ptr = src;

	while (*ptr != '\0')
		ptr++;

	while (*dest != '\0')
	{
		*ptr = *dest;
		ptr++;
		dest++;
	}
	*ptr = '\0';

	return (src);
}
