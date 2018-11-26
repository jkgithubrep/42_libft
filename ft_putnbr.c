/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:14:11 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/26 14:59:52 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{

	long	ln;

	ln = n;
	if (ln < 0)
	{
		ft_putchar('-');
		ln *= -1;
	}
	if (n > 9)
	{
		ft_putnbr(ln / 10);
		ft_putchar((ln % 10) + '0');
	}
	else
		ft_putchar(ln + '0');
}
