/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstforeachif.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 14:18:26 by jkettani          #+#    #+#             */
/*   Updated: 2019/07/18 14:39:43 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstforeachif(t_list *lst, int (*f)(void *), void *ref,
				int (*cmp)())
{
	int		status;

	while (lst)
	{
		if (!(*cmp)(lst->content, ref))
			if ((status = (*f)(lst->content)) != 0)
				return (status);
		lst = lst->next;
	}
	return (0);
}
