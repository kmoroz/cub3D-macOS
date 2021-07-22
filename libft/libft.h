/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 11:43:49 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/07/22 16:21:21 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef struct s_list
{
	char			*row;
	struct s_list	*next;
}				t_list;

int		ft_isalnum(int argument);
int		ft_isalpha(int argument);
int		ft_isdigit(int argument);
int		ft_isspace(int c);
char	*ft_itoa(int n);
void	*ft_memset(void *str, int c, size_t n);
char	*ft_strchr(const char *str, int ch);
char	*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const void *ptr1, const void *ptr2, size_t num);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
t_list	*ft_lstnew(char *content);
char	*ft_strtrim(char const *s1, char const *set);

#endif
