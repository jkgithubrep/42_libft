/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:04:51 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:50:56 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

void	*ft_select_fct(char *fct, char *dst, char *src, size_t n)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "memcpy") == 0)
		ret = (char *)memcpy(dst, src, n);
	else if (strcmp(fct, "ft_memcpy") == 0)
		ret = (char *)ft_memcpy(dst, src, n);
	return ((void *)ret);
}

int		main(int ac, char **av)
{
	char			*dst;
	char			*src;
	char			*ret;
	int				n;
	char			*fct;
	int				nb_arg;


	nb_arg = 4;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		printf("Wrong number of arguments\nUsage: ./memcpy_test fct [null|dest_size] [null|src] n\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		printf("strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") != 0)
	{
		dst = (char *)malloc(sizeof(*dst) * atoi(av[2]));
		if (dst == NULL)
		{
			printf("Memory allocation failed\n");
			return (-1);
		}
		else
		{
			bzero(dst, sizeof(*dst) * atoi(av[2]));
			ft_init_string(dst, sizeof(*dst) * (atoi(av[2]) - 1));
		}
	}
	else
		dst = NULL;
	if (strcmp(av[3], "null") == 0)
		src = NULL;
	else if ((av[3][0] >= '0' && av[3][0] <= '9') || av[3][0] == '-' || av[3][0] == '+')
		src = dst + atoi(av[3]);
	else
		src = av[3];
	n = atoi(av[4]);
	ret = (char *)ft_select_fct(fct, dst, src, n);
	if (strcmp(av[2], "null") != 0)
	{
		printf("dest = ");
		if (dst == NULL)
			printf("NULL");
		else
			print_bytes(dst, sizeof(*dst) * atoi(av[2]));
		printf(" | ");
		printf("ret = ");
		if (ret == NULL)
			printf("NULL");
		else
			print_bytes(ret, sizeof(*dst) * atoi(av[2]));
	}
	free(dst);
	free(fct);
	return (0);
}
