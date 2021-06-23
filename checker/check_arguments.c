/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 12:28:39 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/23 17:21:48 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_extension(char *arg, char *extension)
{
	if (!ft_strnstr(arg, extension, ft_strlen(arg)))
	{
		printf("\U0001f4a9 Invalid file extension \U0001f4a9\n");
		return (ERROR);
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc == 2)
	{
		if (check_extension(argv[1], ".cub") == ERROR)
			exit(ERROR);
	}
	else
	{
		printf("\U0001f4a9 Wrong number of arguments \U0001f4a9\n");
		return (ERROR);
	}
	return (1);
}
