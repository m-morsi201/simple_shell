#include "shell.h"

/**
 * inter_act -func to  returns true if shell is interactive mode.
 * @f: struct pointer.
 * Return: 1 if interactive mode, or 0 if else.
*/
int inter_act(inf_t *f)
{
	return (isatty(STDIN_FILENO) && f->readfd <= 2);
}

/**
 * is_delm - func to check if it delimeter.
 * @ch: it is a char.
 * @del: it is a the delimeter.
 * Return: (1) if true else, (0).
*/

int is_delm(char ch, char *del)
{
	while (*del)
		if (*del++ == ch)
			return (1);
	return (0);
}

/**
 *is_alpha - func to checks for alphabet.
 *@ch: it is a input chars.
 *Return: 1 on alpha, otherwise 0.
*/

int is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *str_to_int - func to converts a string to an integer.
 *@str: it is a string.
 *Return: 0 if no number else, converte number.
*/

int str_to_int(char *str)
{
	int m, s, f, otp;
	unsigned int r;

	r = 0;
	s = 1;
	f = 0;

	for (m = 0;  str[m] != '\0' && f != 2; m++)
	{
		if (str[m] == '-')
			s *= -1;

		if (str[m] >= '0' && str[m] <= '9')
		{
			f = 1;
			r *= 10;
			r += (str[m] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (s == -1)
		otp = -r;
	else
		otp = r;

	return (otp);
}
