/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcountif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:05:41 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/11 13:22:19 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_lstcountif(t_list *lst, void *data_ref, int (*cmp)())
{
	size_t	ret;

	if (!lst || !data_ref || !cmp)
		return (0);
	ret = 0;
	while (lst)
	{
		if (!(*cmp)(lst->content, data_ref))
			++ret;
		lst = lst->next;
	}
	return (ret);
}
