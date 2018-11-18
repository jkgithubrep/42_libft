/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 17:36:14 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/18 20:50:55 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;
	char		ch;
	size_t		i;

	tmp_dst = (char *)dst;
	tmp_src = (const char *)src;
	ch = (char)c;
	i = 0;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		if (tmp_src[i] == ch)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
