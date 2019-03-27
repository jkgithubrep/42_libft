/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_prec_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:41:42 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/20 13:50:04 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBL_PREC_UTILS_H
# define DBL_PREC_UTILS_H

# include "ft_printf.h"

char		*add_exponent_sign(char **val_str, int exponent,
														t_format *conv_params);
char		*trim_zeros(char **val_str, int len);
char		*add_dbl_prec(char **val_str, char *frac_part,
													t_format *conv_params);

#endif
