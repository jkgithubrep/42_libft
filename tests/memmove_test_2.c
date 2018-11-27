/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_test_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:35:56 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/27 13:55:08 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

int		main(void)
{
	char	*src = "first string to test!\n\r";
	char	dst1[100];
	char	dst2[100];
	int		size = strlen(src);

	bzero(dst1, 100);
	bzero(dst2, 100);
	memmove(dst1, src, size);
	ft_memmove(dst2, src, size);
	if (memcmp(dst1, dst2, size) == 0)
		printf("Success\n");
	else 
	{
		printf("Failed\n");
		print_bytes(dst1, size);
		printf("\n");
		print_bytes(dst2, size);
	}
	return (0);
}
