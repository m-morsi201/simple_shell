#include "shell.h"

/**
 *erro_put - fun to print an input str.
 * @s: it is a string to print it.
 * Return: (void).
*/

void erro_put(char *s)
{
	int m;

	m = 0;

	if (!s)
		return;
	while (s[m] != '\0')
	{
		erro_put_ch(s[m]);
		m++;
	}
}

/**
 * erro_put_ch - func to put a character to stderr.
 * @ch: it is a character.
 * Return: (1) if it success, else (-1).
*/

int erro_put_ch(char ch)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(2, buf, m);
		m = 0;
	}
	if (ch != BUF_FLUSH)
		buf[m++] = ch;
	return (1);
}

/**
 * put_fl_des - func to writes the char to fl_des.
 * @ch: it is a char to print it.
 * @fl_des: it is a filedescriptor.
 * Return: (1) if success, else (-1).
*/

int put_fl_des(char ch, int fl_des)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(fl_des, buf, m);
		m = 0;
	}
	if (ch != BUF_FLUSH)
		buf[m++] = ch;
	return (1);
}

/**
 *ps_fldes - func to print an input.
 * @s: it is a string.
 * @fl_des: it is a filedescriptor.
 * Return: number of char.
*/

int ps_fldes(char *s, int fl_des)
{
	int m;

	m = 0;

	if (!s)
		return (0);
	while (*s)
	{
		m += put_fl_des(*s++, fl_des);
	}
	return (m);
}
