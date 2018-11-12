/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:27:05 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/12 18:27:53 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int		main(int ac, char **av)
{
	char	str[17];
	int		i;

	(void)ac;
	(void)av;
	strcpy(str, "Chaine originale");
	ft_print_tab_char(str, sizeof(str)/sizeof(str[0]));
	i = 0;
	while (i < 10)
	{
		ft_putnbr(i);
		ft_putstr(" : ");
		memset(str, i, 7);
		ft_print_tab_char(str, sizeof(str)/sizeof(str[0]));
		i++;
	}
	ft_putchar('\n');
	ft_putchar((char)-256);
	return (0);
}
