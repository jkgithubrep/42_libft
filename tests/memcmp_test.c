/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:26:12 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:50:44 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

int		ft_select_fct(char *fct, const char *s1, const char *s2, size_t n)
{
	int		ret;

	ret = 0;
	if (strcmp(fct, "memcmp") == 0)
		ret = memcmp(s1, s2, n);
	else if (strcmp(fct, "ft_memcmp") == 0)
		ret = ft_memcmp(s1, s2, n);
	return (ret);
}

int		main(int ac, char **av)
{
	char		*s1;
	char		*s2;
	char		*fct;
	int			ret;
	int			n;
	int			nb_arg;


	nb_arg = 4;
	ret = 0;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./memcmp_test fct [null|s1] [null|s2] n\n");
		return (-1);
	}
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("strdup failed: could not get function name");
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
	n = atoi(av[4]);
	ret = ft_select_fct(fct, s1, s2, n);
	ft_putstr("ret = ");
	ft_putnbr(ret);
	free(fct);
	return (0);
}
