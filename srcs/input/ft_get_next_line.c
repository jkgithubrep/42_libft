/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:18:52 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/27 11:25:25 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

#define GNL_BUFF_SIZE 4096

static int	del_saved_buf(char **saved_buf, int ret)
{
	free(*saved_buf);
	*saved_buf = NULL;
	return (ret);
}

static int	save_buf(char **saved_buf, char *prev_buf, char *buf)
{
	char	*tmp;

	tmp = *saved_buf;
	*saved_buf = ft_strjoin(prev_buf, buf);
	if (tmp)
		free(tmp);
	return ((saved_buf) ? 1 : -1);
}

static int	get_line(char **saved_buf, char **line)
{
	char	*new_line;

	if (!(*line = ft_strcdup(*saved_buf, '\n')))
		return (del_saved_buf(saved_buf, -1));
	if ((new_line = ft_strchr(*saved_buf, '\n')))
	{
		if (save_buf(saved_buf, new_line + 1, "") < 0)
			return (del_saved_buf(saved_buf, -1));
	}
	else
	{
		if (save_buf(saved_buf, "", "") < 0)
			return (del_saved_buf(saved_buf, -1));
	}
	return (1);
}

int			ft_get_next_line(const int fd, char **line)
{
	static char		*saved_buf;
	char			buf[GNL_BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	if (!saved_buf)
		save_buf(&saved_buf, "", "");
	if (ft_strchr(saved_buf, '\n'))
		return (get_line(&saved_buf, line));
	while (!ft_strchr(saved_buf, '\n'))
	{
		ret = read(fd, buf, GNL_BUFF_SIZE);
		buf[ret] = 0;
		if (ret < 0)
			return (del_saved_buf(&saved_buf, -1));
		if (ret == 0 && saved_buf[0])
			return (get_line(&saved_buf, line));
		if (ret == 0 && !saved_buf[0])
			return (del_saved_buf(&saved_buf, 0));
		if (save_buf(&saved_buf, saved_buf, buf) < 0)
			return (del_saved_buf(&saved_buf, -1));
	}
	return (get_line(&saved_buf, line));
}
