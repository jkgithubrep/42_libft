/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:05:35 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 19:51:34 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;
	unsigned int	s_len;
	char			*s2;

	i = 0;
	s_len = ft_strlen(s);
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	start = i;
	i = s_len;
	while (i > 0 && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i--;
	end = i;
	s2 = ft_strsub(s, start, end - start + 1);
	if (s2 == NULL)
		return (NULL);
	return (s2);
}
