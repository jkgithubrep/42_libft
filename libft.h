/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:27:18 by jkettani          #+#    #+#             */
/*   Updated: 2018/11/22 12:10:24 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

char	*ft_strcat(char *s, const char *append);
char    *ft_strchr(const char *s, int c);
char    *ft_strrchr(const char *s, int c);
char	*ft_strncat(char *s, const char *append, size_t count);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strdup(const char *s1);
char    *ft_strstr(const char *haystack, const char *needle);
char    *ft_strnstr(const char *haystack, const char *needle, size_t len);
int     ft_atoi(const char *str);
int		ft_isalpha(int c);
int     ft_isdigit(int c);
int     ft_isalnum(int c);
int     ft_isascii(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int     ft_strcmp(const char *s1, const char *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t len);
size_t  ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void    ft_init_string(char *dst, size_t size);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_print_bytes(void *ptr, int size);
void	ft_print_char(char *tab, int size);
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl(char const *s);
void	ft_putendl_fd(char const *s, int fd);
void    ft_putstr(char const *s);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putnbr(int n);
void	ft_putnbr_base(int nbr, char *base);
void	ft_putnbr_fd(int n, int fd);

#endif
