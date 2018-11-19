/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bytes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:01:26 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/19 16:17:52 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_bytes(void *ptr, int size)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)ptr;
	while (i < size)
	{
		ft_putnbr_base(p[i], "0123456789ABCDEF");
		ft_putchar(' ');
		i++;
	}
}
