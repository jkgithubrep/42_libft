/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_formatting_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:16:42 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 16:16:50 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_FORMATTING_UTILS_H
# define INT_FORMATTING_UTILS_H

# include "ft_printf.h"

int				get_nb_zeros_prec(int nb_digits, t_format *conv_params);
int				has_prefix(t_format *conv_params);
char			*prepend_prefix(char **val_str, t_format *conv_params);

#endif
