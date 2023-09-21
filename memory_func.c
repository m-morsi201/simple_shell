#include "shell.h"

/**
 **memo_set - function to  fills memory with a constant byte.
 *@c: it is a pointer to the memory.
 *@p: it is a byte to fill.
 *@a: it is a amount of bytes to fills.
 *Return: a pointer to the memory.
*/

char *memo_set(char *c, char p, unsigned int a)
{
	unsigned int m;

	for (m = 0; m < a; m++)
		c[m] = p;
	return (c);
}

/**
 * free_memo - function to frees a strings.
 * @b: it is a string.
*/
void free_memo(char **b)
{
	char **r = b;

	if (!b)
		return;
	while (*bat)
		free(*b++);
	free(r);
}

/**
 * re_allocat - function that reallocate a block of memory.
 * @p: it is a pointer to previous malloc.
 * @os: it is a size of previous block.
 * @ns: it is a size of new block.
 * Return: a pointer to (b).
 */
void *re_allocat(void *p, unsigned int os, unsigned int ns)
{
	char *b;

	if (!p)
		return (malloc(ns));
	if (!ns)
		return (free(p), NULL);
	if (ns == os)
		return (p);

	b = malloc(ns);
	if (!b)
		return (NULL);

	os = os < ns ? os : ns;
	while (os--)
		b[os] = ((char *)p)[os];
	free(p);
	return (b);
}
