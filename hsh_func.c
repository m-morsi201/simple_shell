#include "shell.h"

/**
 * hsh - func to main shell loop.
 * @inf: it is a parameter struct.
 * @a_v: it is an argument vector.
 * Return: (0) if it success, else (1).
*/

int hsh(inf_t *inf, char **a_v)
{
	ssize_t t = 0;
	int blin_r = 0;

	while (t != -1 && blin_r != -2)
	{
		clr_inf(inf);
		if (inter_act(inf))
			_puts("$ ");
		erro_put_ch(BUF_FLUSH);
		t = get_inp(inf);
		if (t != -1)
		{
			st_inf(inf, a_v);
			blin_r = fnd_bltin(inf);
			if (blin_r == -1)
				fnd_cmd(inf);
		}
		else if (inter_act(inf))
			_putchar('\n');
		fr_inf(inf, 0);
	}
	wr_hist(inf);
	fr_inf(inf, 1);
	if (!inter_act(inf) && inf->stat)
		exit(inf->stat);
	if (blin_r == -2)
	{
		if (inf->err_num == -1)
			exit(inf->stat);
		exit(inf->err_num);
	}
	return (blin_r);
}

/**
 * fnd_bltin - func to finds a builtin command.
 * @inf: it is a parameter struct.
 * Return: -1, 0, 1, -2.
*/

int fnd_bltin(inf_t *inf)
{
	int m, bl_in_r = -1;
	builtin_table blt_intbl[] = {
		{"exit", my_ex},
		{"env", my_env},
		{"help", my_hlp},
		{"history", my_hist},
		{"setenv", my_set_env},
		{"unsetenv", my_unset_env},
		{"cd", myo_cd},
		{"alias", my_als},
		{NULL, NULL}
	};

	for (m = 0; blt_intbl[m].type; m++)
		if (str_comp(inf->argv[0], blt_intbl[m].type) == 0)
		{
			inf->lnc++;
			bl_in_r = blt_intbl[m].func(inf);
			break;
		}
	return (bl_in_r);
}

/**
 * fnd_cmd - func to finds a command in PATH.
 * @inf: it is a parameter struct.
 * Return: void.
*/
void fnd_cmd(inf_t *inf)
{
	char *pth = NULL;
	int m, c;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->lnc++;
		inf->linecount_flag = 0;
	}
	for (m = 0, c = 0; inf->arg[m]; m++)
		if (!is_delm(inf->arg[m], " \t\n"))
			c++;
	if (!c)
		return;

	pth = f_pth(inf, get_env(inf, "PATH="), inf->argv[0]);
	if (pth)
	{
		inf->path = pth;
		frk_cmd(inf);
	}
	else
	{
		if ((inter_act(inf) || get_env(inf, "PATH=")
			|| inf->argv[0][0] == '/') && if_cmd(inf, inf->argv[0]))
			frk_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->stat = 127;
			pr_erro(inf, "not found\n");
		}
	}
}

/**
 * frk_cmd - func to forks a an cmd run .
 * @inf: it is a parameter & return info struct.
 * Return: void
 */
void frk_cmd(inf_t *inf)
{
	pid_t chld_pd;

	chld_pd = fork();
	if (chld_pd == -1)
	{
		perror("Error:");
		return;
	}
	if (chld_pd == 0)
	{
		if (execve(inf->path, inf->argv, get_envn(inf)) == -1)
		{
			fr_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->stat));
		if (WIFEXITED(inf->stat))
		{
			inf->stat = WEXITSTATUS(inf->stat);
			if (inf->stat == 126)
				pr_erro(inf, "Permission denied\n");
		}
	}
}
