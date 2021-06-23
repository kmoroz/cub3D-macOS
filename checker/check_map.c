/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:43:53 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/23 17:17:50 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdio.h>

int	is_line_last(t_cub config)
{
	int		x;

	x = 0;
	config.map = config.map->next;
	if (!config.map)
		return (1);
	while (config.map)
	{
		if (ft_isalnum(config.map->row[x]) || ft_isspace(config.map->row[x]))
			return (0);
		x++;
		config.map = config.map->next;
		x = 0;
	}
	return (1);
}

int	check_blank_lines_in_map(t_cub config)
{
	int		x;

	x = 0;
	while (config.map)
	{
		if (config.map->row[0] == '\0' && !is_line_last(config))
			return (ERROR);
		x++;
		config.map = config.map->next;
		x = 0;
	}
	return (OK);
}

int	is_zero_open(t_cub config, int x, int y)
{
	int	current_row;
	int	previous_row;

	current_row = 0;
	previous_row = y - 1;
	if (previous_row < 0)
		return (ERROR);
	while (config.map && current_row <= y + 1)
	{
		if (current_row == previous_row || current_row == y + 1)
		{
			if (!config.map->row[x] || ft_isspace(config.map->row[x]))
				return (ERROR);
		}
		if (current_row == y)
		{
			if (!config.map->row[x + 1] || ft_isspace(config.map->row[x + 1]))
				return (ERROR);
		}
		config.map = config.map->next;
		current_row++;
	}
	return (1);
}

int	is_map_closed(t_cub config)
{
	int		x;
	int		y;
	int		result;
	t_list	*temp;

	x = 0;
	y = 0;
	result = 0;
	temp = config.map;
	while (temp)
	{
		while ((temp->row[x]))
		{
			if (temp->row[x] == '0' && is_zero_open(config, x, y) == ERROR)
				return (ERROR);
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
	return (1);
}

int	check_map(t_cub config)
{
	if (check_blank_lines_in_map(config) == ERROR)
		return (ERROR);
	if (is_map_closed(config) == ERROR)
		return (ERROR);
	return (OK);
}
