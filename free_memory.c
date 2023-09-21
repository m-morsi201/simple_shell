#include "shell.h"

/**
 * ifree_memo - func to free a pointer.
 * @p: it is a pointer to pointer to free it.
 * Return: 1 if done, otherwise 0.
*/

int ifree_memo(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
