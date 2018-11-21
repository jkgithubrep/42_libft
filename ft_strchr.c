/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:32:07 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/21 10:53:02 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while(*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	return (((char)c == 0) ? (char *)s : NULL);
}