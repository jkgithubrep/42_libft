/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_memset_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:27:30 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/13 20:10:46 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int ac, char **av)
{
	unsigned char	*bs1;
	int				bs2[100] = {0};
	long			bs3[100] = {0};

	(void)ac;
	bs1 = (void *)0;
	if (strcmp(av[1], "NULL") == 0)
		memset(bs1, atoi(av[2]), atoi(av[3]));
	else if (strcmp(av[1], "int[]") == 0)
		memset(bs2, atoi(av[2]), atoi(av[3]));
	else if (strcmp(av[1], "long[]") == 0)
		memset(bs3, atoi(av[2]), atoi(av[3]));
	return (0);
}
