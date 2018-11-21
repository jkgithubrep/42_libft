/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:17:17 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/21 14:50:14 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_select_fct(char *fct, const char *haystack, const char *needle, 
			size_t len)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "strnstr") == 0)
	{
		ret = strnstr(haystack, needle, len);
	}
	else if (strcmp(fct, "ft_strnstr") == 0)
	{
		ret = ft_strnstr(haystack, needle, len);
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
	int				len;


	nb_arg = 4;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./strnstr_test fct [s | null] c\n");
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
	len = atoi(av[4]);
	ret = ft_select_fct(fct, haystack, needle, len);
	ft_putstr("ret = ");
	if (ret == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(ret, sizeof(*ret) * 1);
	free(fct);
	return (0);
}
