#include "shell.h"

/**
 * conv_stoint - func to converts a s to an int.
 * @st: it is a string.
 * Return: 0 if there are numb or, converted number.
 *  (-1) on error.
*/

int conv_stoint(char *st)
{
	int m;
	unsigned long int r;

	m = 0;
	r = 0;

	if (*st == '+')
		st++;
	for (m = 0;  st[m] != '\0'; m++)
	{
		if (st[m] >= '0' && st[m] <= '9')
		{
			r *= 10;
			r += (st[m] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * err_mas - func to print error message.
 * @info: it is an info struct.
 * @ert: it is an error type.
 * Return: (0) no numbers or converted number in string.
 * (-1) if error.
*/

void err_mas(inf_t *info, char *ert)
{
	erro_put(info->fl_name);
	erro_put(": ");
	p_dec(info->lnc, STDERR_FILENO);
	erro_put(": ");
	erro_put(info->argv[0]);
	erro_put(": ");
	erro_put(ert);
}

/**
 * p_dec - func to print a decimal number.
 * @np: it is an input.
 * @fdes: it is a filedescriptor.
 * Return: number of chars that are printed.
*/

int p_dec(int np, int fdes)
{
	int (*put_char)(char) = _putchar;
	int m, c;
	unsigned int a_b_s, cr;

	c = 0;

	if (fdes == STDERR_FILENO)
		put_char = erro_put_ch;
	if (np < 0)
	{
		a_b_s = -np;
		put_char('-');
		c++;
	}
	else
		a_b_s = np;
	cr = a_b_s;
	for (m = 1000000000; m > 1; m /= 10)
	{
		if (a_b_s / m)
		{
			put_char('0' + cr / m);
			c++;
		}
		cr %= m;
	}
	put_char('0' + cr);
	c++;

	return (c);
}

/**
 * convnum - func to convert.
 * @num: it is a number.
 * @bs: it is a base.
 * @fs: it is an argument flags.
 * Return: a string .
*/

char *convnum(long int num, int bs, int fs)
{
	static char *arr;
	static char buffer[50];
	char sn = 0;
	char *pon;
	unsigned long n;

	n = num;

	if (!(fs & CONV_UNS) && num < 0)
	{
		n = -num;
		sn = '-';

	}
	arr = fs & CONV_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	pon = &buffer[49];
	*pon = '\0';

	do	{
		*--pon = arr[n % bs];
		n /= bs;
	} while (n != 0);

	if (sn)
		*--pon = sn;
	return (pon);
}

/**
 * del_comm - function to delete commemts.
 * @buff: it is a pointer to the string.
 * Return: (0).
*/

void del_comm(char *buff)
{
	int m;

	for (m = 0; buff[m] != '\0'; m++)
		if (buff[m] == '#' && (!m || buff[m - 1] == ' '))
		{
			buff[m] = '\0';
			break;
		}
}
