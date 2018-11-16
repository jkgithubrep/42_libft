/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:55:53 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/16 12:38:51 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_select_fct(char *fct, unsigned char *s, size_t n)
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
	unsigned char	*s;
	size_t			n;
	char			*fct;

	s = NULL;
	if (ac == 2 || ac > 4)
	{
		ft_putstr("Wrong number of arguments\nUsage: bzero_test [string_size] nb_bytes\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("strdup failed");
		return (-1);
	}
	if (ac == 3)
	{
		n = (size_t)atoi(av[2]);
		ft_select_fct(fct, s, n);
		ft_print_bytes(s, n);
	}
	if (ac == 4)
	{
		s = (unsigned char *)malloc(sizeof(*s) * atoi(av[2]));
		n = (size_t)atoi(av[3]);
		if (s == NULL)
		{
			ft_putstr("Memory allocation failed.\n");
			return (-1);
		}
		ft_select_fct(fct, s, n);
		ft_print_bytes(s, sizeof(*s) * atoi(av[2]));
	}
	free(s);
	return (0);
}
