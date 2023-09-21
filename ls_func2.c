#include "shell.h"

/**
 * ls_length - func to get length of linked list.
 * @fi_no: it is a pointer to first node.
 * Return: length of linked list.
*/

size_t ls_length(const list_t *fi_no)
{
	size_t m;

	m = 0;

	while (fi_no)
	{
		fi_no = fi_no->next;
		m++;
	}
	return (m);
}

/**
 * ls_to_str - func to return an array of str.
 * @h: it is a ptr to head node.
 * Return: an array of string.
*/
char **ls_to_str(list_t *h)
{
	list_t *no = h;
	size_t m, k;
	char **ss;
	char *s;

	m = ls_length(h);

	if (!h || !m)
		return (NULL);
	ss = malloc(sizeof(char *) * (m + 1));
	if (!ss)
		return (NULL);
	for (m = 0; no; no = no->next, m++)
	{
		s = malloc(str_leng(no->s) + 1);
		if (!s)
		{
			for (k = 0; k < m; k++)
				free(ss[k]);
			free(ss);
			return (NULL);
		}

		s = str_copy(s, no->s);
		ss[m] = s;
	}
	ss[m] = NULL;
	return (ss);
}


/**
 * pr_ls - func to print a list_t linked list.
 * @fir: it is a pointer to first node.
 * Return: a length of linked list.
*/

size_t pr_ls(const list_t *fir)
{
	size_t m = 0;

	while (fir)
	{
		_puts(conv_num(fir->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(fir->s ? fir->s : "(nil)");
		_puts("\n");
		fir = fir->next;
		m++;
	}
	return (m);
}

/**
 * no_begin - func to return node whose begin with prefix.
 * @no: it is a pointer to frist node.
 * @p_fx: it is a str to match with.
 * @ch:  it is the chars to match.
 * Return: (no) or null.
*/

list_t *no_begin(list_t *no, char *p_fx, char ch)
{
	char *prf = NULL;

	while (no)
	{
		prf = begin(no->s, p_fx);
		if (prf && ((ch == -1) || (*prf == ch)))
			return (no);
		no = no->next;
	}
	return (NULL);
}

/**
 * get_no_ind - it a func to get index.
 * @h: it is a pointer to frist node.
 * @no: it is a pointer to node.
 * Return:  (m) or (-1).
*/

ssize_t get_no_ind(list_t *h, list_t *no)
{
	size_t m;

	m = 0;

	while (h)
	{
		if (h == no)
			return (m);
		h = h->next;
		m++;
	}
	return (-1);
}
