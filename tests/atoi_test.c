/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:45:03 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:44:39 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

int		ft_select_fct(char *fct, const char *str)
{
	int		ret;

	ret = 0;
	if (strcmp(fct, "atoi") == 0)
	{
		ret = atoi(str);
	}
	else if (strcmp(fct, "ft_atoi") == 0)
	{
		ret = ft_atoi(str);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char			*fct;
	int				ret;
	int				nb_arg;
	const char		*str;


	nb_arg = 2;
	ret = 0;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./atoi_test fct [s | null]\n");
		return (-1);
	}	
	fct = ft_strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("ft_strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
		str = av[2];
	else
		str = NULL;
	ret = ft_select_fct(fct, str);
	ft_putstr("ret = ");
	ft_putnbr(ret);
	free(fct);
	return (0);
}
