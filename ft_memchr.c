/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:24:19 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 14:50:58 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp_s;
	size_t			i;

	i = 0;
	tmp_s = (unsigned char *)s;
	while (i < n)
	{
		if (tmp_s[i] == (unsigned char)c)
			return ((void *)(tmp_s + i));
		i++;
	}
	return (NULL);
}
