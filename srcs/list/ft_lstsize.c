/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:20:04 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/11 13:23:26 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmp(void *content, void *data_ref)
{
	(void)content;
	(void)data_ref;
	return (0);
}

size_t		ft_lstsize(t_list *lst)
{
	size_t	ret;

	ret = ft_lstcountif(lst, "", &cmp);
	return (ret);
}
