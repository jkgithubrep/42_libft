/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:49:57 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/20 16:33:15 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_select_fct(char *fct, char *s, char *append)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "strcat") == 0)
	{
		ret = strcat(s, append);
	}
	else if (strcmp(fct, "ft_strcat") == 0)
	{
		ret = ft_strcat(s, append);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char			*s;
	char			*append;
	char			*ret;
	char			*fct;
	int				nb_arg;


	nb_arg = 3;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./strcat_test fct [null|s_size] [null|append]\n");
		return (-1);
	}	
	fct = ft_strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("ft_strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
	{
		s = (char *)malloc(sizeof(*s) * atoi(av[2]));
		if (s == NULL)
		{
			ft_putstr("Memory allocation failed\n");
			return (-1);
		}
		else
		{
			ft_bzero(s, sizeof(*s) * atoi(av[2]));
			ft_init_string(s, (sizeof(*s) * atoi(av[2])) / 2);
		}
	}
	else
		s = NULL;
	if (strcmp(av[3], "null") == 0)
		append = NULL;
	else
		append = av[3];
	ret = ft_select_fct(fct, s, append);
	ft_putstr("s = ");
	if (s == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(s, sizeof(*s) * atoi(av[2]));
	ft_putstr(" | ");
	ft_putstr("ret = ");
	if (ret == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(ret, sizeof(*s) * atoi(av[2]));
	free(s);
	free(fct);
	return (0);
}
