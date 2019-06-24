/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmedian.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:29:02 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/24 14:36:04 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int			cmp(int *elm1, int *elm2)
{
	return (*elm1 - *elm2);
}

int					ft_lstmedian(t_list *lst, int (*f)(), int *median)
{
	int				*array;
	int				size;
	t_array_args	args;

	ft_bzero(&args, sizeof(args));
	if (!lst || !median || (size = ft_lstsize(lst)) < 0)
		return (-1);
	if (ft_lsttointarray(lst, &array, f) < 0)
		return (-1);
	args = (t_array_args){array, sizeof(int), size, &cmp};
	ft_mergesort(&args);
	*median = array[size / 2];
	ft_memdel((void **)&array);
	return (0);
}
