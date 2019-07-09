/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstunsortedhasdup.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:04:39 by jkettani          #+#    #+#             */
/*   Updated: 2019/07/09 11:23:45 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*elm_cpy(t_list *elm)
{
	return (ft_lstnew(elm->content, elm->content_size));
}

int				ft_lstunsortedhasdup(t_list **lst, int (*cmp)(),
					void (*del)(void *, size_t))
{
	t_list	*lst_cpy;
	int		ret;

	if (!lst || !*lst || !(*lst)->next)
		return (0);
	if (!(lst_cpy = ft_lstmap(*lst, &elm_cpy, del)))
		return (-1);
	ft_lstmergesort(&lst_cpy, cmp);
	ret = ft_lstsortedhasdup(lst_cpy, cmp);
	ft_lstdel(&lst_cpy, del);
	return (ret);
}
