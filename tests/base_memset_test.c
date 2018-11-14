/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_memset_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:27:30 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/14 10:50:07 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	test_errors(void *(*pf)(void *, int, size_t), char **av)
{
	unsigned char	*bs1;
	unsigned char	bs2[100] = {0};

	bs1 = NULL;
	if (strcmp(av[2], "NULL") == 0)
		pf(bs1, atoi(av[3]), atoi(av[4]));
	else if (strcmp(av[2], "char[]") == 0)
		pf(bs2, atoi(av[3]), atoi(av[4]));
}

int		main(int ac, char **av)
{
	(void)ac;

	if (strcmp(av[1], "ft_memset") == 0)
		test_errors(&ft_memset, av);
	else if (strcmp(av[1], "memset") == 0)
		test_errors(&memset, av);
	return (0);
}
