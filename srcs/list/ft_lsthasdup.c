/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsthasdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:04:39 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/31 17:38:37 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lsthasdup(t_list **lst, int (*cmp)())
{
	t_list	*elm;

	if (!lst || !*lst)
		return (0);
	ft_lstmergesort(lst, cmp);
	elm = *lst;
	while (elm->next)
	{
		if (!(*cmp)(elm->content, elm->next->content))
			return (1);
		elm = elm->next;
	}
	return (0);
}
