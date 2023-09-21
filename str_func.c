#include "shell.h"

/**
 * str_leng - a function will return the length of string.
 * @c: it is a string.
 * Return: length of string.
*/
int str_leng(char *c)
{
	int m;

	m = 0;

	if (!c)
		return (0);
	while (*c++)
		m++;
	return (m);
}

/**
 * str_comp - function to comparison of two strings.
 * @c1: the first string.
 * @c2: the second string.
 * Return: negative or positive or zero.
*/
int str_comp(char *c1, char *c2)
{
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	if (*c1 == *c2)
		return (0);
	else
		return (*c1 < *c2 ? -1 : 1);
}

/**
 * begin - function to checks if need starts with h.
 * @haay: it is a  string to search.
 * @need: it is a another to search.
 * Return: pointer to next char of haay or NULL.
*/
char *begin(const char *haay, const char *need)
{
	while (*need)
		if (*need++ != *haay++)
			return (NULL);
	return ((char *)haay);
}

/**
 * str_concat - function to concatenate two strings.
 * @de: it is a destination of buffer.
 * @sor: it is a source of buffer.
 * Return: pointer to de buffer.
*/
char *str_concat(char *de, char *sor)
{
	char *r;

	r = de;

	while (*de)
		de++;
	while (*sor)
		*de++ = *sor++;
	*de = *sor;

	return (r);
}
