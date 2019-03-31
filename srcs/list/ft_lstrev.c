/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 12:38:20 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/31 13:00:19 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrev(t_list **lst)
{
	t_list 	*prev;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	prev = NULL;
	while (*lst)
	{
		next = (*lst)->next;
		(*lst)->next = prev;
		prev = *lst;
		*lst = next;
	}
	*lst = prev;
}
