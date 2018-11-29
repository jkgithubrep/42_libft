/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 20:13:14 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:51:51 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

void	*ft_select_fct(char *fct, char *dst, char *src)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "strcpy") == 0)
	{
		ret = strcpy(dst, src);
	}
	else if (strcmp(fct, "ft_strcpy") == 0)
	{
		ret = ft_strcpy(dst, src);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char			*dst;
	char			*src;
	char			*ret;
	char			*fct;
	int				nb_arg;


	nb_arg = 3;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./strcpy_test fct [null|dest_size] [null|src]\n");
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
		dst = (char *)malloc(sizeof(*dst) * atoi(av[2]));
		if (dst == NULL)
		{
			ft_putstr("Memory allocation failed\n");
			return (-1);
		}
		else
		{
			ft_bzero(dst, sizeof(*dst) * atoi(av[2]));
			ft_init_string(dst, sizeof(*dst) * (atoi(av[2]) - 1));
		}
	}
	else
		dst = NULL;
	if (strcmp(av[3], "null") == 0)
		src = NULL;
	else
		src = av[3];
	ret = ft_select_fct(fct, dst, src);
	ft_putstr("dest = ");
	if (dst == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(dst, sizeof(*dst) * atoi(av[2]));
	ft_putstr(" | ");
	ft_putstr("ret = ");
	if (ret == NULL)
		ft_putstr("NULL");
	else
		ft_print_bytes(ret, sizeof(*dst) * atoi(av[2]));
	free(dst);
	free(fct);
	return (0);
}
