#include "shell.h"

/**
 * inpt_buff - func to buffers chained commands.
 * @inf: it is a parameter struct.
 * @buff: it is a pointer to buffer.
 * @leng: it is a pointer to len var.
 * Return: the bytes is to read (r)
*/

ssize_t inpt_buff(inf_t *inf, char **buff, size_t *leng)
{
	ssize_t r = 0;
	size_t leng_b = 0;

	if (!*leng)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sig_hndl);
#if USE_GETLINE
		r = getline(buff, &len_b, stdin);
#else
		r = get_ln(inf, buff, &leng_b);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			inf->linecount_flag = 1;
			rem_comm(*buff);
			bld_hist_ls(inf, *buff, inf->histco++);
			{
				*leng = r;
				inf->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * get_inp - func to gets a line minus the newline.
 * @inf: it is a parameter struct.
 * Return: it is return a bytes read.
*/

ssize_t get_inp(inf_t *inf)
{
	static char *buff;
	static size_t m, k, leng;
	ssize_t t = 0;
	char **buff_b = &(inf->arg), *b;

	_putchar(BUF_FLUSH);
	t = inpt_buff(inf, &buff, &leng);
	if (t == -1)
		return (-1);
	if (leng)
	{
		k = m;
		b = buff + m;

		chk_chn(inf, buff, &k, m, leng);
		while (k < leng)
		{
			if (if_chn(inf, buff, &k))
				break;
			k++;
		}

		m = k + 1;
		if (m >= leng)
		{
			m = leng = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buff_b = b;
		return (str_leng(b));
	}

	*buff_b = buff;
	return (t);
}

/**
 * re_buff - func to reads a buffer.
 * @inf: it is a parameter struct.
 * @buff: it is a buffer.
 * @m: it is a size.
 * Return: (r)
 */
ssize_t re_buff(inf_t *inf, char *buff, size_t *m)
{
	ssize_t w = 0;

	if (*m)
		return (0);
	w = read(inf->re_fldes, buff, READ_BUF_SIZE);
	if (w >= 0)
		*m = w;
	return (w);
}

/**
 * get_ln - func to gets the next line of input from STDIN.
 * @inf: it is a parameter struct.
 * @pon: it is pointer to buffer.
 * @lng: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_ln(inf_t *inf, char **pon, size_t *lng)
{
	static char buff[READ_BUF_SIZE];
	static size_t m, lengt;
	size_t kr;
	ssize_t re = 0, h = 0;
	char *b = NULL, *n_b = NULL, *cv;

	b = *pon;
	if (b && lng)
		h = *lng;
	if (m == lengt)
		m = lengt = 0;

	re = re_buff(inf, buff, &lengt);
	if (re == -1 || (re == 0 && lengt == 0))
		return (-1);

	cv = str_char(buff + m, '\n');
	kr = cv ? 1 + (unsigned int)(cv - buff) : lengt;
	n_b = re_allocat(b, h, h ? h + kr : kr + 1);
	if (!n_b)
		return (b ? free(b), -1 : -1);

	if (h)
		str_n_concat(n_b, buff + m, kr - m);
	else
		str_n_copy(n_b, buff + m, kr - m + 1);

	h += kr - m;
	m = kr;
	b = n_b;

	if (lng)
		*lng = h;
	*pon = b;
	return (h);
}

/**
 * sig_hndl - func to blocks a ctrl-C.
 * @sig_n: it is a signal number.
 * Return: void
*/

void sig_hndl(__attribute__((unused))int sig_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
