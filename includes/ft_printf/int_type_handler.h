/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_type_handler.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:28:19 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 15:29:41 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_TYPE_HANDLER_H
# define INT_TYPE_HANDLER_H

# include "ft_printf.h"

char		*get_formatted_str_from_int(t_format *conv_params, va_list args);

#endif
