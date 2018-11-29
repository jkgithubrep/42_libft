/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:02:39 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/29 10:42:19 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"

void	ft_select_fct(char *fct, unsigned char *b, int c, size_t len)
{
	if (strcmp(fct, "memset") == 0)
		memset(b, c, len);
	else if (strcmp(fct, "ft_memset") == 0)
		ft_memset(b, c, len);
}

int		main(int ac, char **av)
{
	char			*fct;
	unsigned char	*b;
	int				c;
	int				nb_arg;
	size_t			len;


	nb_arg = 4;
	if (ac != nb_arg + 1)
	{
		printf("Wrong number of arguments\nUsage: ./memset_test fct [null | string_size] c len\n");
		return (-1);
	}	
	fct = strdup(av[1]);
	if (fct == NULL)
	{
		printf("strdup failed: could not get function name");
		return (-1);
	}
	if (strcmp(av[2], "null") == 0)
		b = NULL;
	else
	{
		b = (unsigned char *)malloc(sizeof(*b) * atoi(av[2]));
		if (b == NULL)
		{
			printf("Memory allocation failed\n");
			return (-1);
		}
		else
			bzero(b, sizeof(*b) * atoi(av[2]));
	}
	c = atoi(av[3]);
	len = atoi(av[4]);
	ft_select_fct(fct, b, c, len);
	printf("dest = ");
	if (b != NULL)
		print_bytes(b, sizeof(*b) * atoi(av[2]));
	else
		printf("NULL");
	free(b);
	return (0);
}
