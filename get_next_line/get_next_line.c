/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/09 09:44:38 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/09 14:03:13 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

int	get_next_line(int fd, char **line)
{
	int		index;
	char	*save;
	int		read_status;
	char	buff[1];

	save = malloc(100000);
	if (!save)
		return (-1);
	index = 0;
	read_status = 0;
	*save = 0;
	read_status = read(fd, buff, 1);
	while (read_status)
	{
		if (*buff == '\n')
			break ;
		save[index] = buff[0];
		index++;
		save[index] = 0;
		read_status = read(fd, buff, 1);
	}
	*line = ft_strdup(save);
	free(save);
	return (read_status);
}
