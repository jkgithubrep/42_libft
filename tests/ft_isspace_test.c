/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:50:38 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/28 09:58:47 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		main(void)
{
	printf("%d", ft_isspace(' '));
	printf("%d", ft_isspace('\t'));
	printf("%d", ft_isspace('\n'));
	printf("%d", ft_isspace('\f'));
	printf("%d", ft_isspace('\r'));
	printf("%d", ft_isspace('\v'));
	printf("%d", ft_isspace('a'));
	printf("%d", ft_isspace('9'));
	printf("%d", ft_isspace('\\'));
	return (0);
}
