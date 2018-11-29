/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_base_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:58:33 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 09:33:38 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		main(void)
{
	int	tab[3];
	int	i;

	tab[0] = 2;
	tab[1] = 10;
	tab[2] = 16;
	i = 0;	
	while (i < 3)
	{
		printf("%s\n", ft_itoa_base(0, tab[i]));
		printf("%s\n", ft_itoa_base(-2, tab[i]));
		printf("%s\n", ft_itoa_base(-10, tab[i]));
		printf("%s\n", ft_itoa_base(-100, tab[i]));
		printf("%s\n", ft_itoa_base(-1234, tab[i]));
		printf("%s\n", ft_itoa_base(-2147483648, tab[i]));
		printf("%s\n", ft_itoa_base(2, tab[i]));
		printf("%s\n", ft_itoa_base(10, tab[i]));
		printf("%s\n", ft_itoa_base(100, tab[i]));
		printf("%s\n", ft_itoa_base(1234, tab[i]));
		printf("%s\n", ft_itoa_base(2147483647, tab[i]));
		i++;
	}
	printf("%s\n", ft_itoa_base(2147483647, 0));
	printf("%s\n", ft_itoa_base(2147483647, 1));
	printf("%s\n", ft_itoa_base(2147483647, 17));
	return (0);
}
