/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spec_parser_utils.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:20:16 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 21:22:05 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_SPEC_PARSER_UTILS_H
# define CONV_SPEC_PARSER_UTILS_H

# include "ft_printf.h"

const char	*save_value_skip_digits(const char *fmt, t_format *conv_params);
const char	*save_prec(const char *fmt, t_format *conv_params, va_list args);
void		save_width(t_format *conv_params, va_list args);

#endif
