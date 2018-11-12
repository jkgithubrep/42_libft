/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:59:26 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/12 16:10:12 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int ac, char **av)
{
	unsigned char	c;
	int				fd;

	(void)ac;
	(void)av;
	c = 'a';
	fd = 1;
	ft_putchar_fd(c, fd);
	ft_putchar('\n');
	return (0);	
}
