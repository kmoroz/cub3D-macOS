/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:43:53 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/20 13:47:40 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include <stdio.h>

int	check_player(t_cub config)
{
	int		x;
	int		y;
	int		count;

	x = 0;
	y = 0;
	count = 0;
	while (config.map)
	{
		while ((config.map->row[x]))
		{
			if (ft_isalpha(config.map->row[x])
				&& !ft_strchr("NSEW", config.map->row[x]))
				return (ERROR);
			else if (ft_strchr("NSEW", config.map->row[x]))
				count++;
			x++;
		}
		config.map = config.map->next;
		y++;
		x = 0;
	}
	if (count == 1)
		return (1);
	return (ERROR);
}

int	check_blank_lines_in_map(t_cub config)
{
	int		x;
	int		y;
	int		count;

	x = 0;
	y = 0;
	count = 0;
	while (config.map)
	{
		while ((config.map->row[x]))
		{
			if (ft_isalnum(config.map->row[x]))
				count++;
			x++;
		}
		if (count == 0)
			return (ERROR);
		config.map = config.map->next;
		y++;
		x = 0;
		count = 0;
	}
	return (1);
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

int is_map_on_top(t_cub config)
{
	if (config.x_res && config.y_res && config.no_texture
		&& config.so_texture && config.we_texture && config.sp_texture && config.ea_texture)
		return (0);
	else
		return (1);
}

int	check_map(t_cub config)
{
	if (check_blank_lines_in_map(config) == ERROR)
		return (ERROR);
	if (is_map_closed(config) == ERROR)
		return (ERROR);
}

int	check_config_file(t_cub config)
{
	if (check_player(config) == ERROR)
	{
		printf("Error\n\U0001f4a9 Invalid player \U0001f4a9\n");
		return (ERROR);
	}
	if (check_map(config) == ERROR)
	{
		printf("Error\n\U0001f4a9 Invalid map \U0001f4a9\n");
		return (ERROR);
	}
	return (1);
}
