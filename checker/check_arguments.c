/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 12:28:39 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/30 13:25:27 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_extension(char *arg, char *extension)
{
	if (!ft_strnstr(arg, extension, ft_strlen(arg)))
		return (ERROR);
	return (OK);
}

void	check_args(int argc, char **argv)
{
	if (argc == 2)
	{
		if (check_extension(argv[1], ".cub") == ERROR)
			ft_error(EXTENSION_INVALID);
	}
	else
		ft_error(ARG_COUNT_WRONG);
}
