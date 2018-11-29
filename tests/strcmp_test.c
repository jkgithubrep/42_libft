/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:58:09 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:51:41 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

int		ft_select_fct(char *fct, const char *s1, const char *s2)
{
	int		ret;

	ret = 0;
	if (strcmp(fct, "strcmp") == 0)
	{
		ret = strcmp(s1, s2);
	}
	else if (strcmp(fct, "ft_strcmp") == 0)
	{
		ret = ft_strcmp(s1, s2);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char			*fct;
	int				ret;
	int				nb_arg;
	const char		*s1;
	const char		*s2;


	nb_arg = 3;
	ret = 0;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./strcmp_test fct [s | null] c\n");
		return (-1);
	}	
	fct = ft_strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("ft_strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
		s1 = av[2];
	else
		s1 = NULL;
	if (strcmp(av[3], "null") != 0)
		s2 = av[3];
	else
		s2 = NULL;
	ret = ft_select_fct(fct, s1, s2);
	ft_putstr("ret = ");
	ft_putnbr(ret);
	free(fct);
	return (0);
}
