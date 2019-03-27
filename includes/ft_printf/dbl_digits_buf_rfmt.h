/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_digits_buf_rfmt.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:23:21 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/20 13:27:27 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBL_DIGITS_BUF_RFMT_H
# define DBL_DIGITS_BUF_RFMT_H

# include "ft_printf.h"

char		*reformat_digits_buf(char **digits, int *exponent,
											t_format *conv_params);

#endif
