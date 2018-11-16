/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:02:39 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/16 16:01:31 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_select_fct(char *fct, unsigned char *b, int c, size_t len)
{
	if (strcmp(fct, "memset") == 0)
	{
		memset(b, c, len);
	}
	else if (strcmp(fct, "ft_memset") == 0)
	{
		ft_memset(b, c, len);
	}
}

int		main(int ac, char **av)
{
	unsigned char	*b;
	int				c;
	size_t			len;
	char			*fct;
	int				nb_arg;


	nb_arg = 4;
	if (ac != nb_arg + 1)
	{
		ft_putstr("Wrong number of arguments\nUsage: ./memset_test fct [null | string_size] c len\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		ft_putstr("strdup failed: could not get function name");
		return (-1);
	}
	if (av[2][0] >= '0' && av[2][0] <= '9')
	{
		b = (unsigned char *)malloc(sizeof(*b) * atoi(av[2]));
		if (b == NULL)
		{
			ft_putstr("Memory allocation failed\n");
			return (-1);
		}
		else
			ft_bzero(b, sizeof(*b) * atoi(av[2]));
	}
	else
		b = NULL;
	c = atoi(av[3]);
	len = atoi(av[4]);
	ft_select_fct(fct, b, c, len);
	if (av[2][0] >= '0' && av[2][0] <= '9')
	{
		ft_print_bytes(b, atoi(av[2]));
	}
	else
		ft_putchar('\n');
	free(b);
	return (0);
}
