/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:50:28 by jkettani          #+#    #+#             */
/*   Updated: 2019/02/25 17:45:47 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcut(char **str, size_t len)
{
	char	*tmp;

	if (!str || len > ft_strlen(*str))
		return (NULL);
	if (!(tmp = ft_strnew(len)))
		return (NULL);
	if (!ft_strncpy(tmp, *str, len))
		return (NULL);
	ft_strdel(str);
	*str = tmp;
	return (*str);
}
