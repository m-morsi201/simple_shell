#include "shell.h"

/**
 **str_n_copy - function to copy a string.
 *@de: it is a destination to string.
 *@sor: it is a source to string.
 *@a: it is a amount of characters.
 *Return: it will return a concatenated string.
*/
char *str_n_copy(char *de, char *sor, int a)
{
	int m, k;
	char *c;

	c = de;
	m = 0;

	while (sor[m] != '\0' && m < (a - 1))
	{
		de[m] = sor[m];
		m++;
	}
	if (m < a)
	{
		k = m;
		while (k < a)
		{
			de[k] = '\0';
			k++;
		}
	}
	return (c);
}

/**
 **str_n_concat - function to concatenates two strings.
 *@de:it is a first string.
 *@sor: it is a second string.
 *@a: it is a amount of bytes.
 *Return: the concatenate string.
*/

char *str_n_concat(char *de, char *sor, int a)
{
	int m, k;
	char *c;

	c = de;
	m = 0;
	k = 0;

	while (de[m] != '\0')
		m++;
	while (sor[k] != '\0' && k < a)
	{
		de[m] = sor[k];
		m++;
		k++;
	}
	if (k < a)
		de[m] = '\0';
	return (c);
}

/**
 **str_char - function to locates a character in a string.
 *@str: it is a string.
 *@ch: it is a character to look for.
 *Return: a pointer to the memory  (str).
*/

char *str_char(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}
