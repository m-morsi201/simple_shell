#include "shell.h"

/**
 * clr_inf - func to initializes info_t struct.
 * @inf: it is a struct pointer.
*/
void clr_inf(inf_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argco = 0;
}

/**
 * st_inf - func to initializes info_t struct.
 * @inf: it is a struct pointer.
 * @a_v: it is an argument vector.
*/
void st_inf(inf_t *inf, char **a_v)
{
	int m;

	m = 0;

	inf->fl_name = a_v[0];
	if (inf->arg)
	{
		inf->argv = str_to_wor(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = str_doup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (m = 0; inf->argv && inf->argv[m]; m++)
			;
		inf->argco = m;

		rep_als(inf);
		rep_vrs(inf);
	}
}

/**
 * fr_inf - func that free inf_t struct.
 * @inf: it is a struct pointer.
 * @alt: if it success will be ture.
*/
void fr_inf(inf_t *inf, int alt)
{
	free_memo(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (alt)
	{
		if (!inf->cmd_buff)
			free(inf->arg);
		if (inf->en_v)
			f_list(&(inf->en_v));
		if (inf->his)
			f_list(&(inf->his));
		if (inf->alts)
			f_list(&(inf->alts));
		free_memo(inf->envn);
			inf->envn = NULL;
		ifree_memo((void **)inf->cmd_buff);
		if (inf->re_fldes > 2)
			close(inf->re_fldes);
		_putchar(BUF_FLUSH);
	}
}
