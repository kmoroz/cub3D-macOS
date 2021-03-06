/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 11:18:47 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/05/24 16:00:09 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *str, int ch)
{
	unsigned char	*modifiable_str;

	modifiable_str = (unsigned char *)str;
	while (*modifiable_str != ch)
	{
		if (*modifiable_str == '\0')
			return (NULL);
		modifiable_str++;
	}
	return ((char *)modifiable_str);
}
