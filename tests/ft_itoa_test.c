/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:28:41 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/28 11:35:56 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		main(void)
{
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(-2));
	printf("%s\n", ft_itoa(-10));
	printf("%s\n", ft_itoa(-100));
	printf("%s\n", ft_itoa(-1234));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(2));
	printf("%s\n", ft_itoa(10));
	printf("%s\n", ft_itoa(100));
	printf("%s\n", ft_itoa(1234));
	printf("%s\n", ft_itoa(2147483647));
	return (0);
}
