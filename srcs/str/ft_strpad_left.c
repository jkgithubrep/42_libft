/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 18:44:20 by jkettani          #+#    #+#             */
/*   Updated: 2019/02/24 20:53:31 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

char		*ft_strpad_left(char **str, int c, size_t len)
{
	char	*prepend;

	if (!str)
		return (NULL);
	if (!(prepend = ft_strcnew(len, c)))
		return (NULL);
	ft_strprepend(prepend, str);
	ft_strdel(&prepend);
	return (*str);
}
