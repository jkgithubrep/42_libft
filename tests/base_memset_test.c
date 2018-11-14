/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_memset_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:27:30 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/14 14:51:29 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int ac, char **av)
{
	unsigned char	*bs1;
	unsigned char	*bs2;

	(void)ac;
	(void)av;
	bs1 = NULL;
	//bs2 = (unsigned char *)malloc(sizeof(*bs2) * 100);
	memset(bs1, 97, -2);
	//memset(bs1, 97, 0);
	//memset(bs1, 97, 140);
	//memset(bs2, 97, -2);
	//memset(bs2, 97, 0);
	//memset(bs2, 97, 50);
	//memset(bs2, 97, 150);
	//(void)ac;
	//bs1 = NULL;
	//if (strcmp(av[1], "NULL") == 0)
	//	memset(bs1, atoi(av[2]), atoi(av[3]));
	//else if (strcmp(av[1], "unsigned_char[100]") == 0)
	//	memset(bs2, atoi(av[2]), atoi(av[3]));
	return (0);
}
