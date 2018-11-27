/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:05:35 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/27 15:53:08 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	unsigned int	start;
	unsigned int	end;

	if (s == NULL)
		return (NULL);
	if (*s == 0)
		return (ft_strdup(s));
	start = 0;
	while (s[start] && ft_isspace(s[start]))
		start++;
	end = (unsigned int)(ft_strlen(s) - 1);
	while (end > start && ft_isspace(s[end]))
		end--;
	return (ft_strsub(s, start, end - start + 1));
}
