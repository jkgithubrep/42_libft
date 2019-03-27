/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:55:07 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/20 13:52:42 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBL_UTILS_H
# define DBL_UTILS_H

# include "ft_printf.h"

char		*handle_dbl_limit_values(t_dbls *arg_val, t_format *conv_params);
char		*handle_dbl_precision(char **digits, int exponent,
													t_format *conv_params);
void		handle_g_conv_spec(int exponent, t_format *conv_params);
int			is_limit_value(t_dbls *arg_val, t_format *conv_params);

#endif
