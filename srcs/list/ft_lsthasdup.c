/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsthasdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:04:39 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/17 15:29:46 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*elm_cpy(t_list *elm)
{
	return (ft_lstnew(elm->content, elm->content_size));
}

int				ft_lsthasdup(t_list **lst, int (*cmp)(),
					void (*del)(void *, size_t))
{
	t_list	*dup;
	t_list	*dup_head;
	int		ret;

	if (!lst || !*lst || !(*lst)->next)
		return (0);
	if (!(dup_head = ft_lstmap(*lst, &elm_cpy, del)))
		return (-1);
	ft_lstmergesort(&dup_head, cmp);
	ret = 0;
	dup = dup_head;
	while (dup->next)
	{
		if (!(*cmp)(dup->content, dup->next->content))
		{
			ret = 1;
			break;
		}
		dup = dup->next;
	}
	ft_lstdel(&dup_head, del);
	return (ret);
}
