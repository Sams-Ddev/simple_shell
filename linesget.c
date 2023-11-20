#include "main.h"

/**
 * input_buf -Buffers a series of chained commands.
 * @info: A structure holding parameters.
 * @buf: The address of the buffer.
 * @len: The address of the variable storing the length.
 *
 * Return: bytes read
 */
ssize_t input_buf(info_r *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*free_ptr((void **)info->cmd_buffer);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, block_Ctrl_c);
#if CALL_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = getNxtline_stdin(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->lineCount_inp = 1;
			comments_remover(*buf);
			addHistoryList(info, *buf, info->count_historyLine++);
			/* if (findChar_inStrg(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buffer = buf;
			}
		}
	}
	return (r);
}

/**
 * getLine_nonLine - Obtains a line of text without including the n/.
 * @info: A structure containing parameters.
 *
 * Return: The number of bytes that were read.
 */
ssize_t getLine_nonLine(info_r *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i;		 /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		chk_chainstats(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (chk_chainDelim(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;	  /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_type_buffer = CMD_NORM;
		}

		*buf_p = p;	/* Returns a pointer to the current command position. */
		return (strLen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from getNxtline_stdin() */
	return (r);	  /* return length of buffer from getNxtline_stdin() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_r *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readInput_fd, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * getNxtline_stdin - Obtains the next line of input from the STDIN.
 * @info: A structure containing parameters.
 * @ptr: The * of a ptr to a buf, which may be preallocated or NULL.
 * @length: The size of the preallocated ptr buffer if it is not NULL.
 *
 * Return: s
 */
int getNxtline_stdin(info_r *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = findChar_inStrg(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = mem_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* WHEN MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		Strg2cat(new_p, buf + i, k - i);
	else
		copyG_strg(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * block_Ctrl_c - Blocks the Ctrl-C signal.
 * @sig_value: The numerical value representing the signal.
 *
 * Return: void
 */
void block_Ctrl_c(__attribute__((unused)) int sig_value)
{
	printsInp_Strg("\n");
	printsInp_Strg("$ ");
	_putchar(BUFFER_FLUSH);
}

