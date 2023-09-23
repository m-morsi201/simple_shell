#include "shell.h"

/**
 * main - it is an entry point.
 * @a_c: it is an argument count.
 * @a_v: it is an argument vector.
 * Return: (0) if it success, else (1).
*/

int main(int a_c, char **a_v)
{
	inf_t inf[] = { INF_IN };
	int fl_des;

	fl_des = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fl_des)
		: "r" (fl_des));

	if (a_c == 2)
	{
		fl_des = open(a_v[1], O_RDONLY);
		if (fl_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				erro_put(a_v[0]);
				erro_put(": 0: Can't open ");
				erro_put(a_v[1]);
				erro_put_ch('\n');
				erro_put_ch(BUF_FLUSH);
				exit(127);
			}

			return (EXIT_FAILURE);
		}
		inf->re_fldes = fl_des;
	}
	popu_env_ls(inf);
	re_hist(inf);
	hsh(inf, a_v);
	return (EXIT_SUCCESS);
}
