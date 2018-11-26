/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:51:49 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/26 21:47:40 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == src || len == 0)
		return (dst);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		tmp_dst = (unsigned char *)dst + len;
		tmp_src = (unsigned char *)src + len;
		while (len--)
			*tmp_dst-- = *tmp_src--;
	}
	return (dst);	
}
