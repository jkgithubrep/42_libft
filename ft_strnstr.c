/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:13:53 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/21 14:46:52 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)	
		{
			i = 1;
			while (haystack[i] == needle[i] && haystack[i] && i < len)
				i++;
			if (i == len)
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
