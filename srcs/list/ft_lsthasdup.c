/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsthasdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:04:39 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/12 12:34:39 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lsthasdup(t_list **lst, int (*cmp)(), t_list *(*cpy)(t_list *elm),
			void (*del)(void *, size_t))
{
	t_list	*elm;
	t_list	*lst_cpy;
	int		ret;

	if (!lst || !*lst || !(*lst)->next)
		return (0);
	if (!(lst_cpy = ft_lstmap(*lst, cpy, del)))
		return (-1);
	ft_lstmergesort(&lst_cpy, cmp);
	if (!(elm = lst_cpy))
		return (-1);
	ret = 0;
	while (elm->next)
	{
		if (!(*cmp)(elm->content, elm->next->content))
		{
			ret = 1;
			break ;
		}
		elm = elm->next;
	}
	ft_lstdel(&lst_cpy, del);
	return (ret);
}
