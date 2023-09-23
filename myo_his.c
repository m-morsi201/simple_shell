#include "shell.h"

/**
 * my_hist - func to  display history list.
 * @inf: it is a structure arguments.
 * Return: Always (0).
*/

int my_hist(inf_t *inf)
{
	pr_ls(inf->his);
	return (0);
}

/**
 * un_set_als - func to sets alias to string.
 * @inf: it is a parameter struct.
 * @s: it is a string alias.
 * Return: Always (0) if it1 success, else (1).
*/
int un_set_als(inf_t *inf, char *s)
{
	char *d, k;
	int r;

	d = str_char(s, '=');
	if (!d)
		return (1);
	k = *d;
	*d = 0;
	r = dn_ind(&(inf->alts),
		get_no_ind(inf->alts, no_begin(inf->alts, s, -1)));
	*d = k;
	return (r);
}

/**
 * set_als - func to sets alias to string.
 * @inf: it is a parameter struct.
 * @s: it is a string alias.
 * Return: (0) if it  success, else (1).
*/

int set_als(inf_t *inf, char *s)
{
	char *b;

	b = str_char(s, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (un_set_als(inf, s));

	un_set_als(inf, s);
	return (add_no_en(&(inf->alts), s, 0) == NULL);
}

/**
 * pr_als - func to print an alias string.
 * @no: it is an alias node.
 * Return: (0) if it  success, else (1).
*/

int pr_als(list_t *no)
{
	char *b = NULL, *z = NULL;

	if (no)
	{
		b = str_char(no->s, '=');
		for (z = no->s; z <= b; z++)
			_putchar(*z);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_als - func to alias builtin.
 * @inf: it is a structure argument prototype.
 * Return: Always (0).
*/

int my_als(inf_t *inf)
{
	int m = 0;
	char *b = NULL;
	list_t *no = NULL;

	if (inf->argco == 1)
	{
		no = inf->alts;
		while (no)
		{
			pr_als(no);
			no = no->next;
		}
		return (0);
	}
	for (m = 1; inf->argv[m]; m++)
	{
		b = str_char(inf->argv[m], '=');
		if (b)
			set_als(inf, inf->argv[m]);
		else
			pr_als(no_begin(inf->alts, inf->argv[m], '='));
	}

	return (0);
}
