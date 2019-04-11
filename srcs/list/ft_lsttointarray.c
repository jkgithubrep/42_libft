/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:12:57 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/11 13:35:44 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_lsttointarray(t_list *lst, int **array, int (*f)())
{
	int		array_size;
	int		i;

	if (!lst || !array || !f)
		return (0);
	array_size = ft_lstsize(lst);
	if (!(*array = (int *)ft_memalloc(sizeof(**array) * array_size)))
		return (0);
	i = 0;
	while (lst)
	{
		(*array)[i++] = (*f)(lst->content);
		lst = lst->next;
	}
	return (i);
}
