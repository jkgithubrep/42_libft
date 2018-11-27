/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:18:03 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/27 10:27:28 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_select_fct(char *fct, const char *s)
{
	size_t	ret;

	ret = 0;
	if (strcmp(fct, "strlen") == 0)
		ret = strlen(s);
	else if (strcmp(fct, "ft_strlen") == 0)
		ret = ft_strlen(s);
	return (ret);
}

int		main(int ac, char **av)
{
	char			*fct;
	size_t			ret;
	int				nb_arg;
	const char		*s;


	nb_arg = 2;
	ret = 0;
	if (ac != nb_arg + 1)
	{
		printf("Wrong number of arguments\nUsage: ./strlen_test fct [s | null]\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		printf("strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
		s = av[2];
	else
		s = NULL;
	ret = ft_select_fct(fct, s);
	printf("ret = ");
	printf("%zd", ret);
	free(fct);
	return (0);
}
