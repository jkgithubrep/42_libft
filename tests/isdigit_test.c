/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:07:45 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 11:30:54 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_select_fct(char *fct, int c)
{
	int		ret;

	ret = 0;
	if (strcmp(fct, "isdigit") == 0)
	{
		ret = isdigit(c);
	}
	else if (strcmp(fct, "ft_isdigit") == 0)
	{
		ret = ft_isdigit(c);
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
		ft_putstr("Wrong number of arguments\nUsage: ./isdigit_test fct [ c | nbr]\n");
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
