#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * _strcpy - copies a string.
 * @dest: destination
 * @src: source
 *
 * Return: final string.
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strcmp - compares two strings.
 * @str1: string one
 * @str2: string two
 *
 * Return: int.
 */
int _strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0')
		{
			return (0);
		}
		i++;
	}

	return ((int)(unsigned char)str1[i] - (int)(unsigned char)str2[i]);
}

/**
 * _strlen - checks the length of str1.
 * @str: strinv to be checked.
 *
 * Description: lenght of @str1.
 *
 * Return: int.
 */
int _strlen(char *str)
{
	int len = 0;

	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}