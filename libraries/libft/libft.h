/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:39:52 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/08 15:36:14 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* LIBRARIES */

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

/* DATA */

# define BUFFER_SIZE 5

/* INT FUNCTIONS */

int		ft_isascii(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isalnum(int cr);
int		ft_isprint(int arg);
int		ft_isalpha(int str);
//int		ft_isdigit(int dgt);
int		ft_atoi(const char *str);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

/* CHAR FUNCTIONS */

char	*ft_itoa(int n);
char	*get_next_line(int reset, int t);
char	*ft_strdup(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *hy, const char *nd, size_t l);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* VOID FUNCTIONS */

void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
void	*ft_memset(void *str, int rp, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/* SIZE_T FUNCTIONS */

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t destSize);
size_t	ft_strlcat(char *dest, const char *src, size_t destSize);

#endif
