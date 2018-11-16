/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bytes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:01:26 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/16 11:23:05 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_print_bytes(void *ptr, int size) 
{
	unsigned char *p;;
	int i;
	
	i = 0;
	p = (unsigned char *)ptr;
	while (i < size)
	{
		printf("%02hhX ", p[i]);
		i++;
	}
	printf("\n");
}

