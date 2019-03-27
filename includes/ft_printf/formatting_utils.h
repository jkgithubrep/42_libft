/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:15:07 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 16:30:56 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMATTING_UTILS_H
# define FORMATTING_UTILS_H

# include "ft_printf.h"

int			get_nb_zeros_prec_dbl(int nb_digits, t_format *conv_params);
char		*prepend_prec(char **val_str, int nb_zeros_prec);
int			has_sign(int nb_zeros_prec, t_format *conv_params);
char		*prepend_sign(char **val_str, t_format *conv_params);
char		*add_padding(char **val_str, int padding, t_format *conv_params);

#endif
