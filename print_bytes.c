/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:35:16 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:41:39 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	print_bytes(const void *s, size_t len)
{
	const unsigned char	*tmp_s;
	size_t				i;

	if (s != NULL && len != 0)
	{
		i = 0;
		tmp_s = (const unsigned char *)s;
		while (i < len)
		{
			printf("%hhX ", tmp_s[i]);
			i++;
		}
	}
}
