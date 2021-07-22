/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:43:53 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/07/22 14:31:13 by ksmorozo      ########   odam.nl         */
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

void	check_blank_lines_in_map(t_cub config)
{
	int		x;

	x = 0;
	while (config.map)
	{
		if (config.map->row[0] == '\0' && !is_line_last(config))
			ft_error(MAP_INVALID);
		x++;
		config.map = config.map->next;
		x = 0;
	}
}

void	is_char_open(t_cub config, int x, int y)
{
	int	current_row;
	int	previous_row;

	current_row = 0;
	previous_row = y - 1;
	if (previous_row < 0)
		ft_error(MAP_INVALID);
	while (current_row <= y + 1)
	{
		if (!config.map)
			ft_error(MAP_INVALID);
		if (current_row == previous_row || current_row == y + 1)
		{
			if (ft_isspace(config.map->row[x]) || !ft_strlen(config.map->row))
				ft_error(MAP_INVALID);
		}
		if (current_row == y)
		{
			if (!config.map->row[x + 1] || ft_isspace(config.map->row[x + 1])
				|| ft_isspace(config.map->row[x - 1]) || (x - 1) < 0)
				ft_error(MAP_INVALID);
		}
		config.map = config.map->next;
		current_row++;
	}
}

void	is_map_closed(t_cub config)
{
	int		x;
	int		y;
	t_list	*temp;

	x = 0;
	y = 0;
	temp = config.map;
	while (temp)
	{
		while (temp->row[x])
		{
			if (ft_strchr("02NSWE", temp->row[x]))
				is_char_open(config, x, y);
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	check_map(t_cub config)
{
	check_blank_lines_in_map(config);
	is_map_closed(config);
	check_allowed_chars(config);
}
