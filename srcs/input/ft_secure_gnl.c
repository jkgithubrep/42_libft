/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 23:08:05 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/02 11:27:12 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_secure_gnl.h"
#include <unistd.h>
#include <limits.h>

static int	del_saved_buf(t_buf *saved_buf, int ret)
{
	free(saved_buf->buf);
	saved_buf->buf = NULL;
	return (ret);
}

static int	save_buf(t_buf *saved_buf, char *new_buf, size_t new_buf_size)
{
	char	*tmp;

	tmp = saved_buf->buf;
	saved_buf->buf = (char *)ft_memjoin(saved_buf->buf, saved_buf->size,
								new_buf, new_buf_size);
	if (tmp)
		free(tmp);
	if (new_buf_size > (size_t)INT_MAX - saved_buf->size)
		return (EXIT_ERR);
	saved_buf->size += new_buf_size;
	return (saved_buf->buf ? 0 : EXIT_ERR);
}

static int	get_line(t_buf *saved_buf, char **line, int *newline)
{
	size_t	ret;
	char	*tmp;

	ret = 0;
	if (!(*line = (char *)ft_memcdup(saved_buf->buf, '\n', saved_buf->size,
				&ret)))
		return (del_saved_buf(saved_buf, EXIT_ERR));
	*newline = (saved_buf->buf[ret] == '\n') ? 1 : 0;
	tmp = saved_buf->buf;
	if (*newline && saved_buf->size > ret + 1)
	{
		saved_buf->size -= ret + 1;
		saved_buf->buf = ft_memdup(saved_buf->buf + ret + 1,
											saved_buf->size);
	}
	else
	{
		saved_buf->size = 0;
		saved_buf->buf = ft_memdup("", 0);
	}
	free(tmp);
	return ((int)ret);
}

int			ft_secure_gnl(const int fd, char **line, int *newline, size_t limit)
{
	static t_buf	saved_buf;
	char			buf[GNL_BUFF_SIZE];
	int				ret;

	if (fd < 0 || !line)
		return (EXIT_ERR);
	if (ft_memchr(saved_buf.buf, '\n', saved_buf.size))
		return (get_line(&saved_buf, line, newline));
	while (!ft_memchr(saved_buf.buf, '\n', saved_buf.size))
	{
		ret = read(fd, buf, GNL_BUFF_SIZE);
		if (ret < 0)
			return (del_saved_buf(&saved_buf, EXIT_ERR));
		if (ret == 0 && saved_buf.size)
			return (get_line(&saved_buf, line, newline));
		if (ret == 0 && !saved_buf.size)
			return (del_saved_buf(&saved_buf, EXIT_EOF));
		if (save_buf(&saved_buf, buf, ret) < 0)
			return (del_saved_buf(&saved_buf, EXIT_ERR));
		if (limit && saved_buf.size > limit)
			return (del_saved_buf(&saved_buf, EXIT_LIM));
	}
	return (get_line(&saved_buf, line, newline));
}
