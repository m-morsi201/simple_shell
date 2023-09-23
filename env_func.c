#include "shell.h"

/**
 * my_env - func to print the environment.
 * @inf: it is a structure arguments.
 * Return: (0) .
*/

int my_env(inf_t *inf)
{
	pls(inf->en_v);
	return (0);
}

/**
 * get_env - func to gets the value of env.
 * @inf: it is a structure arguments.
 * @env_name: name of env.
 * Return: env value.
*/

char *get_env(inf_t *inf, const char *env_name)
{
	list_t *n = inf->en_v;
	char *b;

	while (n)
	{
		b = begin(n->s, env_name);
		if (b && *b)
			return (b);
		n = n->next;
	}
	return (NULL);
}

/**
 * my_set_env - func to initialize a new environment.
 * @inf: it is structure arguments.
 *  Return: (0) or (1).
*/

int my_set_env(inf_t *inf)
{
	if (inf->argco != 3)
	{
		erro_put("Incorrect number of arguements\n");
		return (1);
	}
	if (set_envn(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - func to Remove an environment.
 * @inf: it is a structure argument.
 *  Return: (0).
*/

int my_unset_env(inf_t *inf)
{
	int m;

	if (inf->argco == 1)
	{
		erro_put("Too few arguements.\n");
		return (1);
	}
	for (m = 1; m <= inf->argco; m++)
		unset_envn(inf, inf->argv[m]);

	return (0);
}

/**
 * popu_env_ls -func to  populate env linked list.
 * @inf: it is a structure argument.
 * Return: Always (0).
*/

int popu_env_ls(inf_t *inf)
{
	list_t *n = NULL;
	size_t m;

	for (m = 0; environ[m]; m++)
		add_no_en(&n, environ[m], 0);
	inf->en_v = n;
	return (0);
}
