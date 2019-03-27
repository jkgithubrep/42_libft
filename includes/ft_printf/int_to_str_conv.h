/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_str_conv.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:23:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 16:31:09 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_TO_STR_CONV_H
# define INT_TO_STR_CONV_H

# include "ft_printf.h"

char		*int_arg_val_to_str(intmax_t arg_val, t_format *conv_params);

#endif
