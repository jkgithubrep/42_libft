/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_gnl.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 23:08:23 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/01 23:08:53 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SECURE_GNL_H
# define FT_SECURE_GNL_H

# include <stdlib.h>

# define EXIT_EOF -1
# define EXIT_ERR -2
# define EXIT_LIM -3
# define GNL_BUFF_SIZE 4096

typedef struct		s_buf{
	char			*buf;
	size_t			size;
}					t_buf;

int					ft_secure_gnl(const int fd, char **line, int *newline,
						size_t limit);

#endif
