/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:34:22 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/12 17:54:57 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char(char *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putchar(tab[i]);
		i++;
	}
	ft_putchar('\n');
}
