/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:23:55 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/28 20:59:33 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>

/*
** Fugly hack to suppress unused variable warning
*/

# define UNUSED(x) (void)(x)
# define FALSE 0
# define TRUE !FALSE

typedef int				t_bool;
typedef unsigned char	t_byte;
typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
** Linked lists: libft exclusive
*/

void			ft_lstadd(t_list **alst, t_list *new);

void			ft_lstappend(t_list **alst, t_list *new);

void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_list			*ft_lstnew(const void *content, size_t content_size);

/*
** Reproduction of <ctype.h>
*/

t_bool			ft_isalnum(int c);

t_bool			ft_isalpha(int c);

t_bool			ft_isascii(int c);

t_bool			ft_isblank(int c);

t_bool			ft_iscntrl(int c);

t_bool			ft_isdigit(int c);

t_bool			ft_isgraph(int c);

t_bool			ft_islower(int c);

t_bool			ft_isprint(int c);

t_bool			ft_ispunct(int c);

t_bool			ft_isspace(int c);

t_bool			ft_isupper(int c);

t_bool			ft_isxdigit(int c);

int				ft_toascii(int c);

int				ft_tolower(int c);

int				ft_toupper(int c);

/*
** Reproduction of <stdlib.h>
*/

int				ft_atoi(const char *str);

/*
** Standard I/O: libft exclusive
*/

char			*ft_itoa(int n);

void			ft_putendl(const char *s);

void			ft_putendl_fd(const char *s, int fd);

void			ft_putchar(char c);

void			ft_putchar_fd(char c, int fd);

void			ft_putnbr(int n);

void			ft_putnbr_fd(int n, int fd);

void			ft_putstr(const char *s);

void			ft_putstr_fd(const char *s, int fd);

/*
** Reproduction of <string.h>
*/

void			*ft_memccpy(void *s1, const void *s2, int c, size_t n);

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *s1, const void *s2, size_t n);

void			*ft_memmove(void *s1, const void *s2, size_t n);

void			*ft_memset(void *s, int c, size_t n);

char			*ft_stpcpy(char *s1, const char *s2);

char			*ft_stpncpy(char *s1, const char *s2, size_t n);

char			*ft_strcat(char *s1, const char *s2);

char			*ft_strchr(const char *s, int c);

int				ft_strcmp(const char *s1, const char *s2);

char			*ft_strcpy(char *s1, const char *s2);

char			*ft_strdup(const char *s);

size_t			ft_strlen(const char *s);

char			*ft_strncat(char *s1, const char *s2, size_t n);

int				ft_strncmp(const char *s1, const char *s2, size_t n);

char			*ft_strncpy(char *s1, const char *s2, size_t n);

char			*ft_strndup(const char *s, size_t size);

size_t			ft_strnlen(const char *s, size_t maxlen);

char			*ft_strrchr(const char *s, int c);

char			*ft_strstr(const char *s1, const char *s2);

/*
** POSIX LEGACY <string.h>
*/

void			ft_bzero(void *s, size_t n);

/*
** BSD <string.h>
*/

size_t			ft_strlcat(char *s1, const char *s2, size_t n);

size_t			ft_strlcpy(char *s1, const char *s2, size_t n);

char			*ft_strnstr(const char *s1, const char *s2, size_t n);

/*
** Strings and memory: libft exclusive
*/

void			*ft_memalloc(size_t size);

void			ft_memdel(void **ap);

char			*ft_strcapitalize(char *str);

void			ft_strclr(char *s);

void			ft_strdel(char **as);

int				ft_strequ(const char *s1, const char *s2);

void			ft_striter(char *s, void (*f)(char *));

void			ft_striteri(char *s, void (*f)(unsigned int, char *));

char			*ft_strjoin(const char *s1, const char *s2);

char			*ft_strlowcase(char *str);

char			*ft_strmap(const char *s, char (*f)(char));

char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));

int				ft_strnequ(const char *s1, const char *s2, size_t n);

char			*ft_strnew(size_t size);

char			*ft_strrev(char *str);

char			**ft_strsplit(const char *s, char c);

char			*ft_strsub(const char *s, unsigned int start, size_t len);

char			*ft_strtrim(const char *s);

char			*ft_strupcase(char *str);
#endif
