/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:25:49 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/27 14:55:47 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

int		main(void)
{
	char	*s1 = "";
	char	*s2;
	
	s2 = ft_strtrim(s1);	
	if (s2 == NULL)
		return (-1);
	printf("%s\n", s2);
	return (0);
}
