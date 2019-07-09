/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:56:32 by jkettani          #+#    #+#             */
/*   Updated: 2019/07/09 16:49:22 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstiter(t_list *lst, void *ref, int (*f)(void *, t_list *))
{
	int	status;

	if (!lst || !f)
		return (-1);
	while (lst)
	{
		status = (*f)(ref, lst);
		if (status != 0)
			return (status);
		lst = lst->next;
	}
	return (0);
}
