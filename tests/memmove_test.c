/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:46:44 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:51:07 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

void	*ft_select_fct(char *fct, char *dst, char *src, size_t len)
{
	char	*ret;

	ret = NULL;
	if (strcmp(fct, "memmove") == 0)
		ret = (char *)memmove(dst, src, len);
	else if (strcmp(fct, "ft_memmove") == 0)
		ret = (char *)ft_memmove(dst, src, len);
	return ((void *)ret);
}

int		main(int ac, char **av)
{
	char			*dst;
	char			*src;
	char			*ret;
	int				len;
	char			*fct;
	int				nb_arg;


	nb_arg = 4;
	ret = NULL;
	if (ac != nb_arg + 1)
	{
		printf("Wrong number of arguments\nUsage: ./memmove_test fct [null|dest_size] [null|src] n\n");
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
			ft_bzero(dst, sizeof(*dst) * atoi(av[2]));
			ft_init_string(dst, sizeof(*dst) * (atoi(av[2]) - 1));
		}
	}
	else
		dst = NULL;
	if (strcmp(av[3], "null") != 0)
	{
		src = av[3];
	}
	else
		src = NULL;
	len = atoi(av[4]);
	ret = (char *)ft_select_fct(fct, dst, src, len);
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
		print_bytes(ret, 1);
	free(dst);
	free(fct);
	return (0);
}
