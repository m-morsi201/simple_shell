#include "shell.h"

/**
 * my_ex - func to exit from shell.
 * @inf: it is structure arguments.
 *  Return: exits with a given exit status.
*/

int my_ex(inf_t *inf)
{
	int if_exit;

	if (inf->argv[1])
	{
		if_exit = erro_at_cmd(inf->argv[1]);
		if (if_exit == -1)
		{
			inf->stat = 2;
			pr_erro(inf, "Illegal number: ");
			erro_put(inf->argv[1]);
			erro_put_ch('\n');
			return (1);
		}
		inf->err_num = erro_at_cmd(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * myo_cd - func to changes the current directory.
 * @inf:  it is a structure arguments.
 *  Return: Always (0).
*/

int myo_cd(inf_t *inf)
{
	char *c, *direc, buf[1024];
	int cdr_r;

	c = getcwd(buf, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		direc = get_env(inf, "HOME=");
		if (!direc)
			cdr_r = /* TODO: what should this be? */
				chdir((direc = get_env(inf, "PWD=")) ? direc : "/");
		else
			cdr_r = chdir(direc);
	}
	else if (str_comp(inf->argv[1], "-") == 0)
	{
		if (!get_env(inf, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(inf, "OLDPWD=")), _putchar('\n');
		cdr_r = /* TODO: what should this be? */
			chdir((direc = get_env(inf, "OLDPWD=")) ? direc : "/");
	}
	else
		cdr_r = chdir(inf->argv[1]);
	if (cdr_r == -1)
	{
		pr_erro(inf, "can't cd to ");
		erro_put(inf->argv[1]), erro_put_ch('\n');
	}
	else
	{
		set_envn(inf, "OLDPWD", get_env(inf, "PWD="));
		set_envn(inf, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * my_hlp - func to change current dir.
 * @inf: it is a structure arguments.
 *  Return: Always (0).
*/

int my_hlp(inf_t *inf)
{
	char **arg_arr;

	arg_arr = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
