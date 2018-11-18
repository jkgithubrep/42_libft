/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 13:15:18 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/18 15:25:39 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_base_size(char *base)
{
	int	i;

	i = 0;
	while (*base++)
		i++;
	return (i);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long	n;
	int		base_s;

	n = nbr;
	base_s = ft_base_size(base);
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= base_s)
	{
		ft_putnbr_base(n / base_s, base);
		ft_putchar(base[n % base_s]);
	}
	else
		ft_putchar(base[n]);
}
