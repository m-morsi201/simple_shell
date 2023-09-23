#include "shell.h"

/**
 * if_cmd - func to determine if a file is a command.
 * @inf: it is a info struct.
 * @pth: it is a path to the file.
 * Return: (1) if true, else (0).
*/

int if_cmd(inf_t *inf, char *pth)
{
	struct stat s;

	(void)inf;
	if (!pth || stat(pth, &s))
		return (0);

	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_ch - func to duplicates characters.
 * @pthstr: it is a PATH string.
 * @begin: it is a starting index.
 * @stp: it is a stopping index.
 * Return: it return a pointer to new buffer
 */
char *dup_ch(char *pthstr, int begin, int stp)
{
	static char buff[1024];
	int m = 0, u = 0;

	for (u = 0, m = begin; m < stp; m++)
		if (pthstr[m] != ':')
			buff[u++] = pthstr[m];
	buff[u] = 0;
	return (buff);
}

/**
 * f_pth - func to find a cmd in the PATH string.
 * @inf: it is a info struct.
 * @pthstr: it is a  PATH string
 * @cmd: it is a cmd to find
 * Return: the full path of cmd if found, else  NULL.
*/

char *f_pth(inf_t *inf, char *pthstr, char *cmd)
{
	int m = 0, cur_pth = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((str_leng(cmd) > 2) && begin(cmd, "./"))
	{
		if (if_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[m] || pthstr[m] == ':')
		{
			pth = dup_ch(pthstr, cur_pth, m);
			if (!*pth)
				str_concat(pth, cmd);
			else
			{
				str_concat(pth, "/");
				str_concat(pth, cmd);
			}
			if (if_cmd(inf, pth))
				return (pth);
			if (!pthstr[m])
				break;
			cur_pth = m;
		}
		m++;
	}
	return (NULL);
}
