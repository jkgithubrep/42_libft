/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:15:28 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 19:53:11 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

unsigned int	ft_str_size(int n)
{
	long			a;
	unsigned int	neg;

	a = n;
	neg = 1;
	if (a < 0)
	{
		neg++;
		a *= -1;
	}
	if (a > 9)
	{
		return (neg + ft_str_size(a / 10));
	}
	else
		return (neg);
}

void			ft_fill_str(int n, char *str, int i)
{
	long	a;

	a = n;
	if (a < 0)
	{
		str[0] = '-';
		a *= -1;
	}
	if (a > 9)
	{
		ft_fill_str(a / 10, str, i - 1);
		str[i] = (a % 10) + '0';
	}
	else
		str[i] = (a % 10) + '0';
}

char			*ft_itoa(int n)
{
	unsigned int	size;
	char			*str;

	size = ft_str_size(n);
	str = (char *)malloc(sizeof(*str) * (size + 1));
	if (str == NULL)
		return (NULL);
	ft_fill_str(n, str, size - 1);
	str[size] = 0;
	return (str);
}
