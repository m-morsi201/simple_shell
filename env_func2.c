#include "shell.h"

/**
 * get_envn - func to return array copy of environ.
 * @inf: it is a structure argument.
 * Return: Always (0).
*/

char **get_envn(inf_t *inf)
{
	if (!inf->envn || inf->env_chn)
	{
		inf->envn = ls_to_str(inf->en_v);
		inf->env_chn = 0;
	}

	return (inf->envn);
}

/**
 * unset_envn - func to remove environment.
 * @inf: it is a structure arguments.
 * @vr: it is a str variable.
 * Return: (1) if success, else (0).
*/

int unset_envn(inf_t *inf, char *vr)
{
	list_t *n = inf->en_v;
	size_t m = 0;
	char *b;

	if (!n || !vr)
		return (0);

	while (n)
	{
		b = begin(n->s, vr);
		if (b && *b == '=')
		{
			inf->env_chn = dn_ind(&(inf->en_v), m);
			m = 0;
			n = inf->en_v;
			continue;
		}
		n = n->next;
		m++;
	}
	return (inf->env_chn);
}

/**
 * set_envn -  func initialize environment variable.
 * @inf:  it is a structure arguments.
 * @vr: it is a the string env var property.
 * @vl: it is a the string env var value.
 *  Return: Always (0)
*/

int set_envn(inf_t *inf, char *vr, char *vl)
{
	char *buff = NULL;
	list_t *n;
	char *b;

	if (!vr || !vl)
		return (0);

	buff = malloc(str_leng(vr) + str_leng(vl) + 2);
	if (!buff)
		return (1);
	str_copy(buff, vr);
	str_concat(buff, "=");
	str_concat(buff, vl);
	n = inf->en_v;
	while (n)
	{
		b = begin(n->s, vr);
		if (b && *b == '=')
		{
			free(n->s);
			n->s = buff;
			inf->env_chn = 1;
			return (0);
		}
		n = n->next;
	}
	add_no_en(&(inf->en_v), buff, 0);
	free(buff);
	inf->env_chn = 1;
	return (0);
}
