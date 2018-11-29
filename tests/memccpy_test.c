/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 16:41:55 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:50:20 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

void	*ft_select_fct(char *fct, char *dst, char *src, int c, size_t n)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "memccpy") == 0)
	{
		ret = (char *)memccpy(dst, src, c, n);
	}
	else if (strcmp(fct, "ft_memccpy") == 0)
	{
		ret = (char *)ft_memccpy(dst, src, c, n);
	}
	return ((void *)ret);
}

int		main(int ac, char **av)
{
	char			*dst;
	char			*src;
	char			*ret;
	int				n;
	int				c;
	char			*fct;
	int				nb_arg;


	nb_arg = 5;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./memccpy_test fct [null|dest_size] [null|src] n\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
	{
		dst = (char *)malloc(sizeof(*dst) * atoi(av[2]));
		if (dst == NULL)
		{
			ft_putstr("Memory allocation failed\n");
			return (-1);
		}
		else
		{
			ft_bzero(dst, sizeof(*dst) * atoi(av[2]));
			ft_init_string(dst, sizeof(*dst) * (atoi(av[2]) - 1));
		}
	}
	else
		dst = NULL;
	if (strcmp(av[3], "null") != 0)
	{
		src = av[3];
	}
	else
		src = NULL;
	if (atoi(av[4]) == 0)
		c = av[4][0];
	else
		c = atoi(av[4]);
	n = atoi(av[5]);
	ret = (char *)ft_select_fct(fct, dst, src, c, n);
	if (strcmp(av[2], "null") != 0)
	{
		ft_putstr("dest = ");
		ft_print_bytes(dst, sizeof(*dst) * atoi(av[2]));
		ft_putstr(" | ");
		ft_putstr("ret = ");
		if (ret == NULL)
			ft_putstr("NULL");
		else
			ft_print_bytes(ret, 1);
	}
	free(dst);
	free(fct);
	return (0);
}
