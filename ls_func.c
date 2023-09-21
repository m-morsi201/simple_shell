#include "shell.h"

/**
 * add_no_fi - func to add a node in start.
 * @h: it is pointer to pointer to head node.
 * @s: it is a string.
 * @n: it is a node index.
 * Return: (nh)size of list or NULL.
*/

list_t *add_no_fi(list_t **h, const char *s, int n)
{
	list_t *nh;

	if (!h)
		return (NULL);
	nh = malloc(sizeof(list_t));
	if (!nh)
		return (NULL);
	memo_set((void *)nh, 0, sizeof(list_t));
	nh->n = n;
	if (s)
	{
		nh->s = str_doup(s);
		if (!nh->s)
		{
			free(nh);
			return (NULL);
		}
	}
	nh->next = *h;
	*h = nh;
	return (nh);
}

/**
 * add_no_en - func to add a node in end.
 * @h: it is pointer to pointer to head node.
 * @s: it is a string.
 * @n: it is a node index.
 * Return: (n_no) size of list or NULL.
*/
list_t *add_no_en(list_t **h, const char *s, int n)
{
	list_t *n_no, *no;

	if (!h)
		return (NULL);

	no = *h;
	n_no = malloc(sizeof(list_t));
	if (!n_no)
		return (NULL);
	memo_set((void *)n_no, 0, sizeof(list_t));
	n_no->n = n;
	if (s)
	{
		n_no->s = str_doup(s);
		if (!n_no->s)
		{
			free(n_no);
			return (NULL);
		}
	}
	if (no)
	{
		while (no->next)
			no = no->next;
		no->next = n_no;
	}
	else
		*h = n_no;
	return (n_no);
}

/**
 * pls - func to print only the string element.
 * @fir: pointer to first node.
 * Return: (i) the size of list.
*/

size_t pls(const list_t *fir)
{
	size_t m;

	m = 0;

	while (fir)
	{
		_puts(fir->s ? fir->s : "(nil)");
		_puts("\n");
		fir = fir->next;
		m++;
	}
	return (m);
}

/**
 * dn_ind - func to delete node at index.
 * @h: pointer to pointer to first node.
 * @ind: it is index to delete.
 * Return: (1) if success, else (0).
*/

int dn_ind(list_t **h, unsigned int ind)
{
	list_t *no, *pr_no;
	unsigned int m;

	m = 0;

	if (!h || !*h)
		return (0);

	if (!ind)
	{
		no = *h;
		*h = (*h)->next;
		free(no->s);
		free(no);
		return (1);
	}
	no = *h;
	while (no)
	{
		if (m == ind)
		{
			pr_no->next = no->next;
			free(no->s);
			free(no);
			return (1);
		}
		m++;
		pr_no = no;
		no = no->next;
	}
	return (0);
}

/**
 * f_list - func to free all nodes of lists.
 * @h_ptr: pointer to first node.
 * Return: (void) or NULL.
*/

void f_list(list_t **h_ptr)
{
	list_t *no, *n_no, *h;

	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	no = h;
	while (no)
	{
		n_no = no->next;
		free(no->s);
		free(no);
		no = n_no;
	}
	*h_ptr = NULL;
}
