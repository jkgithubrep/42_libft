/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:32:27 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/12 15:13:20 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int ac, char **av)
{
	unsigned char	c;

	(void)ac;
	(void)av;
	c = 0xDA;
	ft_putchar(c);
	c = 0xB7;
	ft_putchar(c);
	ft_putchar('\n');
	return (0);	
}
