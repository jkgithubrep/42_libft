/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:13:53 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 13:06:57 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	count;

	count = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (count < len && *haystack)
	{
		if (*haystack == *needle)
		{
			i = 1;
			while (haystack[i] == needle[i] && haystack[i] && count + i < len)
				i++;
			if (needle[i] == 0)
				return ((char *)haystack);
		}
		haystack++;
		count++;
	}
	return (NULL);
}
