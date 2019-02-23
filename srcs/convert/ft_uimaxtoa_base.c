/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimaxtoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 17:37:30 by jkettani          #+#    #+#             */
/*   Updated: 2019/02/23 20:05:19 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char		*ft_uimaxtoa_base(uintmax_t nb, int radix)
{
	int		digits;
	char	*str;
	char	*base;

	if ((digits = ft_udigits_base(nb, radix)) < 0
			|| !(str = (char *)ft_strnew(digits)))
		return (NULL);
	base = "0123456789ABCDEF";
	while (digits > 0)
	{
		str[digits - 1] = base[nb % radix];
		nb /= radix;
		--digits;
	}
	return (str);
}
