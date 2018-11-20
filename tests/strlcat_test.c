/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:05:30 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/20 18:19:41 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_select_fct(char *fct, char *dst, char *src, size_t dstsize)
{
	size_t	ret;

	ret = 0;
	if (strcmp(fct, "strlcat") == 0)
	{
		ret = strlcat(dst, src, dstsize);
	}
	else if (strcmp(fct, "ft_strlcat") == 0)
	{
		ret = ft_strlcat(dst, src, dstsize);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char			*dst;
	char			*src;
	int				dstsize;
	size_t			ret;
	char			*fct;
	int				nb_arg;


	nb_arg = 4;
	ret = 0;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./strlcat_test fct [null|s_size] [null|src]\n");
		return (-1);
	}	
	fct = ft_strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("ft_strdup failed: could not get function name");
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
			ft_init_string(dst, (sizeof(*dst) * atoi(av[2])) / 2);
		}
	}
	else
		dst = NULL;
	if (strcmp(av[3], "null") == 0)
		src = NULL;
	else
		src = av[3];
	dstsize = atoi(av[4]);
	ret = ft_select_fct(fct, dst, src, dstsize);
	ft_putstr("dst = ");
	if (dst == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(dst, sizeof(*dst) * atoi(av[2]));
	ft_putstr(" | ");
	ft_putstr("ret = ");
	ft_putnbr(ret);
	free(dst);
	free(fct);
	return (0);
}
