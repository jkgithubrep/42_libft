/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isascii_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 11:50:02 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 11:50:47 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_select_fct(char *fct, int c)
{
	int		ret;

	ret = 0;
	if (strcmp(fct, "isascii") == 0)
	{
		ret = isascii(c);
	}
	else if (strcmp(fct, "ft_isascii") == 0)
	{
		ret = ft_isascii(c);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char			*fct;
	int				ret;
	int				nb_arg;
	int				c;


	nb_arg = 2;
	ret = 0;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./isascii_test fct [ c | nbr]\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("ft_strdup failed: could not get function name");
		return (-1);
	}
	if (ft_strlen(av[2]) > 1)
		c = ft_atoi(av[2]);
	else
		c = av[2][0];
	ret = ft_select_fct(fct, c);
	ft_putstr("ret = ");
	ft_putnbr(ret);
	free(fct);
	return (0);
}
