/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltobendian.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:00:36 by jkettani          #+#    #+#             */
/*   Updated: 2019/07/09 15:02:04 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_ltobendian(unsigned int nb)
{
	return (((nb >> 24) & 0x000000ff)
			| ((nb >> 8) & 0x0000ff00)
			| ((nb << 8) & 0x00ff0000)
			| ((nb << 24) & 0xff000000));
}
