#include "shell.h"

/**
 * str_copy - function to copy a string.
 * @de: it is a destination.
 * @sor: it is a source.
 * Return: it will return a pointer to destination.
*/

char *str_copy(char *de, char *sor)
{
	int m;

	m = 0;

	if (de == sor || sor == 0)
		return (de);
	while (sor[m])
	{
		de[m] = sor[m];
		m++;
	}
	de[m] = 0;
	return (de);
}

/**
 * str_doup - it is a function to duplicate a string.
 * @s: it is a string.
 * Return: it will return pointer to the duplicated string.
 */

char *str_doup(const char *s)
{
	int len;
	char *r;

	len = 0;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--s;
	return (r);
}

/**
 *_puts - function to print an input string.
 *@s: it is a string to print.
 *Return: (void) .
*/

void _puts(char *s)
{
	int m;

	m = 0;

	if (!s)
		return;
	while (s[m] != '\0')
	{
		_putchar(s[m]);
		m++;
	}
}

/**
 * _putchar - function to write a character.
 * @ch: The character to print
 * Return: 1 or -1.
*/

int _putchar(char ch)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(1, buf, m);
		m = 0;
	}
	if (ch != BUF_FLUSH)
		buf[m++] = ch;
	return (1);
}
