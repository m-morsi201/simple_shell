#include "shell.h"

/**
 * erro_at_cmd - func to convert a string to an int.
 * @str: it is a string.
 * Return: (0) if no num in string, else (-1).
*/

int erro_at_cmd(char *str)
{
	int m = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (m = 0;  str[m] != '\0'; m++)
	{
		if (str[m] >= '0' && str[m] <= '9')
		{
			res *= 10;
			res += (str[m] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * pr_erro - func to print an error.
 * @inf: it is a parameter struct.
 * @st_err: it is a string error.
 * Return: (0) if no numbers in string, else (-1).
*/

void pr_erro(inf_t *inf, char *st_err)
{
	erro_put(inf->fl_name);
	erro_put(": ");
	pr_dec(inf->lnc, STDERR_FILENO);
	erro_put(": ");
	erro_put(inf->argv[0]);
	erro_put(": ");
	erro_put(st_err);
}

/**
 * pr_dec - function to print a decimal num.
 * @input: it is a input.
 * @fldes: it is a filedescriptor to write to.
 * Return: number of characters printed
 */
int pr_dec(int input, int fldes)
{
	int (*pch)(char) = _putchar;
	int m, cun = 0;
	unsigned int _abs_, crnt;

	if (fldes == STDERR_FILENO)
		pch = erro_put_ch;
	if (input < 0)
	{
		_abs_ = -input;
		pch('-');
		cun++;
	}
	else
		_abs_ = input;
	crnt = _abs_;
	for (m = 1000000000; m > 1; m /= 10)
	{
		if (_abs_ / m)
		{
			pch('0' + crnt / m);
			cun++;
		}
		crnt %= m;
	}
	pch('0' + crnt);
	cun++;

	return (cun);
}

/**
 * conv_num - func to converter number.
 * @num: it is a number.
 * @b: it is a base.
 * @flg: it is an argument flags.
 * Return: it will return string.
*/

char *conv_num(long int num, int b, int flg)
{
	static char *arr;
	static char buff[50];
	char s = 0;
	char *pon;
	unsigned long v = num;

	if (!(flg & CONV_UNS) && num < 0)
	{
		v = -num;
		s = '-';

	}
	arr = flg & CONV_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	pon = &buff[49];
	*pon = '\0';

	do	{
		*--pon = arr[v % b];
		v /= b;
	} while (v != 0);

	if (s)
		*--pon = s;
	return (pon);
}

/**
 * rem_comm - function remove first instance of '#'.
 * @buff: it is a buffer to the string.
 * Return: Always (0).
*/

void rem_comm(char *buff)
{
	int m;

	for (m = 0; buff[m] != '\0'; m++)
		if (buff[m] == '#' && (!m || buff[m - 1] == ' '))
		{
			buff[m] = '\0';
			break;
		}
}
