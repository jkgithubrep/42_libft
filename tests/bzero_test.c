/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:55:53 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/19 12:55:08 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_select_fct(char *fct, char *s, size_t n)
{
	if (strcmp(fct, "bzero") == 0)
	{
		bzero(s, n);
	}
	else if (strcmp(fct, "ft_bzero") == 0)
	{
		ft_bzero(s, n);
	}
}

int		main(int ac, char **av)
{
	char			*s;
	int				n;
	char			*fct;
	int				nb_arg;

	nb_arg = 3;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: bzero_test [string_size] nb_bytes\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("strdup failed: could not get function name");
		return (-1);
	}
	n = atoi(av[3]);
	if (strcmp(av[2], "null") != 0)
	{
		s = (char *)malloc(sizeof(*s) * atoi(av[2]));
		if (s == NULL)
		{
			ft_putstr("Memory allocation failed.\n");
			return (-1);
		}
		else
			ft_init_string(s, sizeof(*s) * atoi(av[2]));
	}
	else
		s = NULL;
	ft_select_fct(fct, s, n);
	ft_putstr("dest = ");
	if (s == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(s, sizeof(*s) * atoi(av[2]));
	free(s);
	return (0);
}