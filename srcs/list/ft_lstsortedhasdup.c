/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsortedhasdup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:04:39 by jkettani          #+#    #+#             */
/*   Updated: 2019/07/09 11:23:33 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_lstsortedhasdup(t_list *lst, int (*cmp)())
{
	if (!lst || !lst->next)
		return (0);
	while (lst->next)
	{
		if (!(*cmp)(lst->content, lst->next->content))
			return (1);
		lst = lst->next;
	}
	return (0);
}
