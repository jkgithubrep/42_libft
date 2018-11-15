/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:55:53 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/15 19:53:21 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void print_bytes(void *ptr, int size) 
{
	unsigned char *p = ptr;
	int i;
	for (i=0; i<size; i++) {
		printf("%02hhX ", p[i]);
	}
	printf("\n");
}

int		main(int ac, char **av)
{
	char	*s;
	size_t	n;
	int		i;

	(void)ac;
	(void)av;
	//if (ac != 3)
	//{
	//	ft_putstr("Wrong number of arguments\nUsage: bzero_test s_size n\n");
	//	return (-1);
	//}
	//s = (char *)malloc(sizeof(*s) * atoi(av[1]));
	//n = (size_t)atoi(av[2]);
	//if (s == NULL)
	//{
	//	ft_putstr("Memory allocation failed.\n");
	//	return (-1);
	//}
	//bzero(s, n);
	s = (char *)malloc(sizeof(*s) * 2);
	n = 10;
	bzero(s, n);
	i = 123;
	print_bytes(&i, sizeof(i));
	return (0);
}
