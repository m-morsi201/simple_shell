#include "shell.h"

/**
 * **str_to_wor - func to splits a string into words.
 * @s: it is a string as input.
 * @del: it is a delimeter string.
 * Return: an addres to an array of strings, or NULL.
*/

char **str_to_wor(char *s, char *del)
{
	int m, k, e, w, num_wor;
	char **c;

	num_wor = 0;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (m = 0; s[m] != '\0'; m++)
		if (!is_delm(s[m], del) && (is_delm(s[m + 1], del) || !s[m + 1]))
			num_wor++;

	if (num_wor == 0)
		return (NULL);
	c = malloc((1 + num_wor) * sizeof(char *));
	if (!c)
		return (NULL);
	for (m = 0, k = 0; k < num_wor; k++)
	{
		while (is_delm(s[m], del))
			m++;
		e = 0;
		while (!is_delm(s[m + e], del) && s[m + e])
			e++;
		c[k] = malloc((e + 1) * sizeof(char));
		if (!c[k])
		{
			for (e = 0; e < k; e++)
				free(c[e]);
			free(c);
			return (NULL);
		}
		for (w = 0; w < e; w++)
			c[k][w] = s[m++];
		c[k][w] = 0;
	}
	c[k] = NULL;
	return (c);
}

/**
 * **str_to_wor2 - func to splits a string into words.
 * @s: it is a input string.
 * @del: it is a delimeter.
 * Return: an address to an array, or NULL.
*/

char **str_to_wor2(char *s, char del)
{
	int m, k, e, w, num_wor;
	char **c;

	num_wor = 0;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (m = 0; s[m] != '\0'; m++)
		if ((s[m] != del && s[m + 1] == del) ||
		    (s[m] != del && !s[m + 1]) || s[m + 1] == del)
			num_wor++;
	if (num_wor == 0)
		return (NULL);
	c = malloc((1 + num_wor) * sizeof(char *));
	if (!c)
		return (NULL);
	for (m = 0, k = 0; k < num_wor; k++)
	{
		while (s[m] == del && s[m] != del)
			m++;
		e = 0;
		while (s[m + e] != del && s[m + e] && s[m + e] != del)
			e++;
		c[k] = malloc((e + 1) * sizeof(char));
		if (!c[k])
		{
			for (e = 0; e < k; e++)
				free(c[e]);
			free(c);
			return (NULL);
		}
		for (w = 0; w < e; w++)
			c[k][w] = s[m++];
		c[k][w] = 0;
	}
	c[k] = NULL;
	return (c);
}
