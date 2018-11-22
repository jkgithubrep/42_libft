/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:31:30 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 15:26:45 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_select_fct(char *fct, const char *s, int c, size_t n)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "memchr") == 0)
	{
		ret = (char *)memchr(s, c, n);
	}
	else if (strcmp(fct, "ft_memchr") == 0)
	{
		ret = (char *)ft_memchr(s, c, n);
	}
	return ((void *)ret);
}

int		main(int ac, char **av)
{
	char			*s;
	char			*ret;
	int				c;
	int				n;
	char			*fct;
	int				nb_arg;


	nb_arg = 4;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./memchr_test fct [null|s_size] c n\n");
		return (-1);
	}
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
		s = av[2];
	else
		s = NULL;
	if ((av[3][0] >= '0' && av[3][0] <= '9') || av[3][0] == '-' || av[3][0] == '+')
		c = atoi(av[3]);
	else
		c = av[3][0];
	n = atoi(av[4]);
	ret = (char *)ft_select_fct(fct, s, c, n);
	ft_putstr("ret = ");
	if (ret == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(ret, sizeof(*ret) * 1);
	free(fct);
	return (0);
}
