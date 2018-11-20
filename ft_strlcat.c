/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:52:59 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/20 18:15:32 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		while ((i + dst_len < dstsize - 1) && src[i])
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return ((dstsize < dst_len) ? src_len + dstsize : src_len + dst_len);
}
