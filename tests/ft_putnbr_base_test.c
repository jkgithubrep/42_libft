/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:28:38 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 09:54:14 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		main(void)
{
	int i;

	i = -10;
	while (i <= 10)
	{
		ft_putnbr_base(i, 2);
		ft_putchar(' ');
		ft_putnbr_base(i, 10);
		ft_putchar(' ');
		ft_putnbr_base(i, 16);
		ft_putchar('\n');
		i++;
	}
	ft_putnbr_base(-2147483648, 2);
	ft_putchar(' ');
	ft_putnbr_base(-2147483648, 10);
	ft_putchar(' ');
	ft_putnbr_base(-2147483648, 16);
	ft_putchar('\n');
	ft_putnbr_base(2147483647, 2);
	ft_putchar(' ');
	ft_putnbr_base(2147483647, 10);
	ft_putchar(' ');
	ft_putnbr_base(2147483647, 16);
	ft_putchar('\n');
	ft_putnbr_base(2147483647, 0);
	ft_putchar(' ');
	ft_putnbr_base(2147483647, 1);
	ft_putchar(' ');
	ft_putnbr_base(2147483647, 17);
	ft_putchar('\n');
	return (0);
}
