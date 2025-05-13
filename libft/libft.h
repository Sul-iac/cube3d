/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:27:06 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/06 08:44:48 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../includes/get_next_line.h"

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_tolower(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_isascii(int c);
int					ft_atoi(const char *str);
int					ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strdup(const char *str);
char				*ft_itoa(int n);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(const char *s, char c);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
const char			*ft_strnstr(const char *str, const char *to_find, size_t n);


size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t destsize);


void				*ft_memset(void *b, int c, size_t len);
void				*ft_bzero(void *b, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

typedef struct st_list
{
	void			*content;
	struct st_list	*next;
}					tu_list;

tu_list				*ft_lstnew(void *content);
void				ft_lstadd_front(tu_list **alst, tu_list *new);
int					ft_lstsize(tu_list *lst);
tu_list				*ft_lstlast(tu_list *lst);
void				ft_lstadd_back(tu_list **lst, tu_list *new);
void				ft_lstdelone(tu_list *lst, void (*del)(void*));
void				ft_lstclear(tu_list **lst, void (*del)(void*));


#endif