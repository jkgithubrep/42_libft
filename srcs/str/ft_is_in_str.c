/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:14:43 by jkettani          #+#    #+#             */
/*   Updated: 2019/02/22 11:20:12 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
** Check if char argument `c` is in string `str`. Terminating null character in
** `str` is not taken into account.
** Return value: returns zero if c is not found in the string  and non-zero
**               if the character tests true.
*/
int				ft_is_in_str(const char c, const char *str)
{
	char		*ptr;

	ptr = ft_strchr(str, c);
	return (!!ptr && *ptr);
}
