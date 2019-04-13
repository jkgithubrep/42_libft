/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsthasdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:04:39 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/13 10:47:35 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*elm_cpy(t_list *elm)
{
	return (ft_lstnew(elm->content, elm->content_size));
}

int		ft_lsthasdup(t_list **lst, int (*cmp)(), void (*del)(void *, size_t))
{
	t_list	*dup;

	if (!lst || !*lst || !(*lst)->next)
		return (0);
	if (!(dup = ft_lstmap(*lst, &elm_cpy, del)))
		return (-1);
	ft_lstmergesort(&dup, cmp);
	while (dup->next)
	{
		if (!(*cmp)(dup->content, dup->next->content))
			return (1);
		dup = dup->next;
	}
	return (0);
}
