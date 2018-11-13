/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:12:23 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/13 17:12:32 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_str(char *str, size_t size)
{
	bzero(str, size);
	strcpy(str, "String to change");
}

int		main(int ac, char **av)
{
	char	str[50];
	size_t	len;
	int		c;
	size_t	size;

	if (ac != 3)
	{
		ft_putstr("Wrong number of arguments.\nUsage: .out char len\n");
		return (-1);
	}
	size = sizeof(str)/sizeof(str[0]);
	//Initialize string
	init_str(str, size);
	//Display original string
	ft_print_tab_char(str, size);
	//Define variables
	c = atoi(av[1]);
	len = atoi(av[2]);
	//Display variables
	ft_putstr("c = ");
	ft_putnbr(c);
	ft_putchar('\n');
	ft_putstr("len = ");
	ft_putnbr(len);
	ft_putchar('\n');
	memset(str, c, len);
	ft_putstr("ft_memset:\n");
	ft_putstr("  > libc: ");
	ft_print_tab_char(str, size);
	//Reinitialize and test user function
	init_str(str, size);
	ft_memset(str, c, len);
	ft_putstr("  > user: ");
	ft_print_tab_char(str, size);
	return (0);
}
