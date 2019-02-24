/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpreprend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 18:09:28 by jkettani          #+#    #+#             */
/*   Updated: 2019/02/24 19:08:46 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strprepend(const char *prepend, char **str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = *str;
	*str = ft_strjoin(prepend, tmp);
	ft_strdel(&tmp);
	return (*str);
}
