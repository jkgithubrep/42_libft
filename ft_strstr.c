/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:14:57 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 11:15:16 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			i = 1;
			while (haystack[i] == needle[i] && haystack[i])
				i++;
			if (needle[i] == 0)
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
