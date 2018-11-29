/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:55:53 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:44:54 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

void	ft_select_fct(char *fct, char *s, size_t n)
{
	if (strcmp(fct, "bzero") == 0)
		bzero(s, n);
	else if (strcmp(fct, "ft_bzero") == 0)
		ft_bzero(s, n);
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
		printf("Wrong number of arguments\nUsage: bzero_test [string_size] nb_bytes\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		printf("strdup failed: could not get function name");
		return (-1);
	}
	n = atoi(av[3]);
	if (strcmp(av[2], "null") != 0)
	{
		s = (char *)malloc(sizeof(*s) * atoi(av[2]));
		if (s == NULL)
		{
			printf("Memory allocation failed.\n");
			return (-1);
		}
		else
			ft_init_string(s, sizeof(*s) * atoi(av[2]));
	}
	else
		s = NULL;
	ft_select_fct(fct, s, n);
	printf("dest = ");
	if (s == NULL)
		printf("NULL");
	else
		print_bytes(s, sizeof(*s) * atoi(av[2]));
	free(s);
	return (0);
}
