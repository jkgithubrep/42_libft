/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:46:44 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/19 12:08:41 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_select_fct(char *fct, char *dst, char *src, size_t len)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "memmove") == 0)
	{
		ret = (char *)memmove(dst, src, len);
	}
//	else if (strcmp(fct, "ft_memmove") == 0)
//	{
//		ret = (char *)ft_memmove(dst, src, len);
//	}
	return ((void *)ret);
}

int		main(int ac, char **av)
{
	char			*dst;
	char			*src;
	char			*ret;
	int				len;
	char			*fct;
	int				nb_arg;


	nb_arg = 4;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./memmove_test fct [null|dest_size] [null|src] n\n");
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
			ft_init_string(dst, sizeof(*dst) * atoi(av[2]) - 1);
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
	len = atoi(av[4]);
	ret = (char *)ft_select_fct(fct, dst, src, len);
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
	else
	free(dst);
	free(fct);
	return (0);
}
