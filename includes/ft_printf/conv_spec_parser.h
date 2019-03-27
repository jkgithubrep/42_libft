/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spec_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 13:34:15 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 20:37:19 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_SPEC_PARSER_H
# define CONV_SPEC_PARSER_H

const char			*parse_conv_spec(const char *fmt, t_format *conv_params,
															va_list args);

#endif
