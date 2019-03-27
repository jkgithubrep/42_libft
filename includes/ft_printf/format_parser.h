/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 13:28:03 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 20:15:14 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_PARSER_H
# define FORMAT_PARSER_H

int				parse_fmt(t_worker *work, t_format *conv_params,
										const char **fmt, va_list args);
int				add_to_buff(t_worker *work, char *val_str, int len);
int				save_buf(t_worker *work);

#endif
