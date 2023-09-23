#include "shell.h"

/**
 * get_histf - func to get history file.
 * @inf: it is info struct.
 * Return: allocated file history.
*/

char *get_histf(inf_t *inf)
{
	char *b, *d;

	d = get_env(inf, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (str_leng(d) + str_leng(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	str_copy(b, d);
	str_concat(b, "/");
	str_concat(b, HIST_FILE);
	return (b);
}

/**
 * wr_hist - func to create a file.
 * @inf: it is a struct.
 * Return: (1) if it success, else (-1).
*/

int wr_hist(inf_t *inf)
{
	ssize_t fldes;
	char *file_name = get_histf(inf);
	list_t *no = NULL;

	if (!file_name)
		return (-1);

	fldes = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fldes == -1)
		return (-1);
	for (no = inf->his; no; no = no->next)
	{
		ps_fldes(no->s, fldes);
		put_fl_des('\n', fldes);
	}
	put_fl_des(BUF_FLUSH, fldes);
	close(fldes);
	return (1);
}

/**
 * re_hist - func to read history from file.
 * @inf: it is a struct.
 * Return: histco if it  success, else (0).
*/

int re_hist(inf_t *inf)
{
	int m, l = 0, lnc = 0;
	ssize_t fldes, rd_l, fs = 0;
	struct stat s_t;
	char *buff = NULL, *fl_name = get_histf(inf);

	if (!fl_name)
		return (0);

	fldes = open(fl_name, O_RDONLY);
	free(fl_name);
	if (fldes == -1)
		return (0);
	if (!fstat(fldes, &s_t))
		fs = s_t.st_size;
	if (fs < 2)
		return (0);
	buff = malloc(sizeof(char) * (fs + 1));
	if (!buff)
		return (0);
	rd_l = read(fldes, buff, fs);
	buff[fs] = 0;
	if (rd_l <= 0)
		return (free(buff), 0);
	close(fldes);
	for (m = 0; m < fs; m++)
		if (buff[m] == '\n')
		{
			buff[m] = 0;
			bld_hist_ls(inf, buff + l, lnc++);
			l = m + 1;
		}
	if (l != m)
		bld_hist_ls(inf, buff + l, lnc++);
	free(buff);
	inf->histco = lnc;
	while (inf->histco-- >= HIST_MAX)
		dn_ind(&(inf->his), 0);
	renum_hist(inf);
	return (inf->histco);
}

/**
 * bld_hist_ls - func to add entry to a history.
 * @inf: it is a structure arguments.
 * @buff: it is a buffer.
 * @ln_co: it is a history linecount.
 * Return: Always (0).
*/

int bld_hist_ls(inf_t *inf, char *buff, int ln_co)
{
	list_t *no = NULL;

	if (inf->his)
		no = inf->his;
	add_no_en(&no, buff, ln_co);

	if (!inf->his)
		inf->his = no;
	return (0);
}

/**
 * renum_hist - func to renumber the history linked list.
 * @inf: it is a structure arguments.
 * Return: it is a new histcount.
*/

int renum_hist(inf_t *inf)
{
	list_t *no = inf->his;
	int m = 0;

	while (no)
	{
		no->n = m++;
		no = no->next;
	}
	return (inf->histco = m);
}
