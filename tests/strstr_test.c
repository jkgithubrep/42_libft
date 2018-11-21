/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:36:00 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/21 12:47:00 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_select_fct(char *fct, const char *haystack, const char *needle)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "strstr") == 0)
	{
		ret = strstr(haystack, needle);
	}
	else if (strcmp(fct, "ft_strstr") == 0)
	{
		ret = ft_strstr(haystack, needle);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char			*fct;
	char			*ret;
	int				nb_arg;
	const char		*haystack;
	const char		*needle;


	nb_arg = 3;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./strstr_test fct [s | null] c\n");
		return (-1);
	}	
	fct = ft_strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("ft_strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
		haystack = av[2];
	else
		haystack = NULL;
	if (strcmp(av[3], "null") != 0)
		needle = av[3];
	else
		needle = NULL;
	ret = ft_select_fct(fct, haystack, needle);
	ft_putstr("ret = ");
	if (ret == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(ret, sizeof(*ret) * 1);
	free(fct);
	return (0);
}
