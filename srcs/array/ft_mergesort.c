/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:19:16 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/24 14:06:41 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		assign(void *dst, void *src, t_array_args *a)
{
	ft_memcpy(dst, src, a->elmt_size);
}

static int		merge(t_array_args *a, int left, int mid, int right)
{
	void	*tmp_arr;
	size_t	scale;
	t_pos	p;

	scale = a->elmt_size;
	p = (t_pos){0, left, mid + 1};
	if (!(tmp_arr = (void *)ft_memalloc(a->elmt_size * (right - left + 1))))
		return (-1);
	while (p.left <= mid && p.right <= right)
	{
		if ((*(a->cmp))(a->arr + p.left * scale,
				a->arr + p.right * scale) < 0)
			assign(tmp_arr + p.cur++ * scale, a->arr + p.left++ * scale, a);
		else
			assign(tmp_arr + p.cur++ * scale, a->arr + p.right++ * scale, a);
	}
	while (p.left <= mid)
		assign(tmp_arr + (p.cur++ * scale), a->arr + (p.left++ * scale), a);
	while (p.right <= right)
		assign(tmp_arr + p.cur++ * scale, a->arr + p.right++ * scale, a);
	while (p.cur--)
		assign(a->arr + (left + p.cur) * scale, tmp_arr + p.cur * scale, a);
	ft_memdel((void **)&tmp_arr);
	return (0);
}

static int		array_merge_sort(t_array_args *a, int left, int right)
{
	int		mid;

	if (!a || !a->arr || (left >= right))
		return (0);
	mid = (left + right) / 2;
	return (array_merge_sort(a, left, mid) != 0
		|| array_merge_sort(a, mid + 1, right) != 0
		|| merge(a, left, mid, right) != 0);
}

int				ft_mergesort(t_array_args *a)
{
	if (array_merge_sort(a, 0, a->nb_elmt - 1) != 0)
		return (-1);
	return (0);
}
