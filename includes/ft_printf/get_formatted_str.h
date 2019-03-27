/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_formatted_str.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:22:09 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 16:22:36 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_FORMATTED_STR_H
# define GET_FORMATTED_STR_H

# include "ft_printf.h"

char	*get_formatted_str_from_char(t_format *conv_params, va_list args);
char	*get_formatted_str_from__str(t_format *conv_params, va_list args);
char	*get_formatted_str(t_format *conv_params, va_list args);

#endif
