/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:38:34 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/28 14:41:36 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			**ft_strsplit(char const *s, char c)
{
	char	**tb;
	int		nbw;
	int		i;

	if (s == NULL)
		return (NULL);
	nbw = ft_count_words_c(s, c);
	tb = (char **)malloc(sizeof(*tb) * (nbw + 1));
	if (tb == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			tb[i] = ft_strdup_c(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	tb[i] = NULL;
	return (tb);
}
