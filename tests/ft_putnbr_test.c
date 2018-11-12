/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:21:26 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/12 15:38:25 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int		i;
	int		tab_size;
	int		tab[] = {-1000, -10, -3, -1, 0, 1, 5, 10, 100, 1000, -2147483648,
						2147483647};
	i = 0;
	tab_size = sizeof(tab)/sizeof(tab[0]);
	while (i < tab_size)
	{
		ft_putnbr(tab[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}
