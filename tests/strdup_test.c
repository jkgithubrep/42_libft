/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 19:37:33 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:51:59 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "tests.h"

char	*ft_select_fct(char *fct, char *s1)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "strdup") == 0)
	{
		ret = strdup(s1);
	}
	else if (strcmp(fct, "ft_strdup") == 0)
	{
		ret = ft_strdup(s1);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char	*ret;
	char	*fct;
	char	*s1;
	int		nb_arg;


	nb_arg = 2;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./strdup_test fct [s1 | null] \n");
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
	ret = ft_select_fct(fct, s1);
	ft_putstr("ret = ");
	if (ret == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(ret, sizeof(*ret) * (ft_strlen(s1) + 1));
	free(fct);
	return (0);
}
