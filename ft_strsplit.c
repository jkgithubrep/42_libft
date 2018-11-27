/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:38:34 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/27 15:36:30 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_count_words(char const *s, char c)
{
	unsigned int	nb;

	nb = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			nb++;
			while (*s && *s != c)
				s++;
		}
	}
	return (nb);
}

char			*ft_strdupw(char const *s, char c)
{
	char	*dst;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dst = (char *)malloc(sizeof(*dst) * (i + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tb;
	int		nbw;
	int		i;

	if (s == NULL)
		return (NULL);
	nbw = ft_count_words(s, c);
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
			tb[i] = ft_strdupw(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	tb[i] = NULL;
	return (tb);
}
