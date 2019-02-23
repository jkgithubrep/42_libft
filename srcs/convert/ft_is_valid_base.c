/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 20:09:13 by jkettani          #+#    #+#             */
/*   Updated: 2019/02/23 20:23:10 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_is_valid_base(const char *base)
{
	int		i;
	int		j;
	char	c;

	if (!base || !*base)
		return (0);
	i = 0;
	while (base[i])
	{
		if (ft_issign(base[i]) || !ft_isprint(base[i]))
			return (0);
		j = i;
		while (base[++j])
			if (base[j] == base[i])
				return (0);
		i++;
	}
	return (1);
}
