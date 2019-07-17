/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 10:52:47 by jkettani          #+#    #+#             */
/*   Updated: 2019/07/17 11:34:56 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstremoveif(t_list **alst, void *ref, int (*cmp)(),
					void (*del)(void *, size_t))
{
	t_list		*lst;
	t_list		*prev;
	t_list		*tmp;

	lst = *alst;
	prev = NULL;
	while (lst)
	{
		if (!(*cmp)(lst->content, ref))
		{
			if (prev)
				prev->next = lst->next;
			else
				*alst = lst->next;
			tmp = lst;
			lst = lst->next;
			ft_lstdelone(&tmp, del);
		}
		else
		{
			prev = lst;
			lst = lst->next;
		}
	}
}
