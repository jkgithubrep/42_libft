/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bytes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:01:26 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/16 18:00:19 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_print_bytes(void *ptr, int size, char *fmt) 
{
	unsigned char *p;;
	int i;
	
	i = 0;
	p = (unsigned char *)ptr;
	if ((strcmp(fmt, "hex") != 0) && (strcmp(fmt, "char") != 0))
	{
		printf("Wrong format (hex or char)\n");
		return ;
	}
	while (i < size)
	{
		if (strcmp(fmt, "hex") == 0)
		{
			printf("%02hhX ", p[i]);
		}
		else if (strcmp(fmt, "char") == 0)
		{
			printf("%c ", p[i]);
		}
		i++;
	}
	printf("\n");
}

