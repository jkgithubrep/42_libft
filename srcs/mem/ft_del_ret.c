/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_ret.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:50:23 by jkettani          #+#    #+#             */
/*   Updated: 2019/07/24 19:00:09 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int			ft_del_ret(void *content, size_t content_size,
				void (*del)(void *, size_t), int ret)
{
	(*del)(content, content_size);
	return (ret);
}
