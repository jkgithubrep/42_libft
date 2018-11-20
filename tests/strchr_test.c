/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:36:46 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/20 18:52:26 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_select_fct(char *fct, const char *s, int c)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "strchr") == 0)
	{
		ret = strchr(s, c);
	}
	else if (strcmp(fct, "ft_strchr") == 0)
	{
		ret = ft_strchr(s, c);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char			*fct;
	char			*ret;
	int				c;
	int				nb_arg;
	const char		*s;


	nb_arg = 3;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./strchr_test fct [s | null] c\n");
		return (-1);
	}	
	fct = ft_strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("ft_strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
		s = av[2];
	else
		s = NULL;
	c = atoi(av[3]);
	ret = ft_select_fct(fct, s, c);
	ft_putstr("ret = ");
	if (ret == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(ret, sizeof(*ret) * 1);
	free(fct);
	return (0);
}
