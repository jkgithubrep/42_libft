/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 18:44:20 by jkettani          #+#    #+#             */
/*   Updated: 2019/02/24 20:44:04 by jkettani         ###   ########.fr       */
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

int		main(void)
{
	char 	*str;
	char	*ret;

	str = ft_strdup("chaine12");
	printf("%s\n", str);
	ret = ft_strpad_left(&str, '_', 10);
	printf("%s\n", str);
	ft_strdel(&str);
}
