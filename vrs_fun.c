#include "shell.h"

/**
 * if_chn - func to test if current ch in buffer is a chain.
 * @inf: it is a parameter struct.
 * @buff: it is a char buffer.
 * @b: it is a pointer to current position in buf.
 * Return: (1) if chain, else (0).
*/

int if_chn(inf_t *inf, char *buff, size_t *b)
{
	size_t k = *b;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buff[k] = 0;
		k++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[k] == '&' && buff[k + 1] == '&')
	{
		buff[k] = 0;
		k++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[k] == ';') /* found end of this command */
	{
		buff[k] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*b = k;
	return (1);
}

/**
 * chk_chn - func to check continue chaining.
 * @inf: it is a the parameter struct.
 * @buff: it is the char buffer.
 * @b: it is a pointer to current position.
 * @m: it is start position in buf.
 * @leng: it is a length of buf.
 * Return: (Void) nothing.
*/

void chk_chn(inf_t *inf, char *buff, size_t *b, size_t m, size_t leng)
{
	size_t k = *b;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->stat)
		{
			buff[m] = 0;
			k = leng;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->stat)
		{
			buff[m] = 0;
			k = leng;
		}
	}

	*b = k;
}

/**
 * rep_als - func to replaces an aliases.
 * @inf: it is a parameter struct.
 * Return: (1) if replaced, else  (0).
*/

int rep_als(inf_t *inf)
{
	int m;
	list_t *no;
	char *b;

	for (m = 0; m < 10; m++)
	{
		no = no_begin(inf->alts, inf->argv[0], '=');
		if (!no)
			return (0);
		free(inf->argv[0]);
		b = str_char(no->s, '=');
		if (!b)
			return (0);
		b = str_doup(b + 1);
		if (!b)
			return (0);
		inf->argv[0] = b;
	}
	return (1);
}

/**
 * rep_vrs - func to  replaces vars in the tokenized string.
 * @inf: it is a parameter struct.
 * Return: (1) if success, else (0).
*/

int rep_vrs(inf_t *inf)
{
	int m = 0;
	list_t *no;

	for (m = 0; inf->argv[m]; m++)
	{
		if (inf->argv[m][0] != '$' || !inf->argv[m][1])
			continue;

		if (!str_comp(inf->argv[m], "$?"))
		{
			rep_str(&(inf->argv[m]),
				str_doup(conv_num(inf->stat, 10, 0)));
			continue;
		}
		if (!str_comp(inf->argv[m], "$$"))
		{
			rep_str(&(inf->argv[m]),
				str_doup(conv_num(getpid(), 10, 0)));
			continue;
		}
		no = no_begin(inf->en_v, &inf->argv[m][1], '=');
		if (no)
		{
			rep_str(&(inf->argv[m]),
				str_doup(str_char(no->s, '=') + 1));
			continue;
		}
		rep_str(&inf->argv[m], str_doup(""));

	}
	return (0);
}

/**
 * rep_str - func to replaces string.
 * @o: it is a pointer to old string.
 * @n: it is a new string.
 * Return: (1) if success, else (0).
*/

int rep_str(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
