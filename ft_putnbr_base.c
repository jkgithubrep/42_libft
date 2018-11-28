/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 13:15:18 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/28 14:38:22 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int nbr, char *base)
{
	long	n;
	int		base_s;

	n = nbr;
	base_s = ft_strlen(base);
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
