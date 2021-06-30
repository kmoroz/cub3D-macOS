/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:09:14 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/30 11:43:10 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <fcntl.h>
#include <stddef.h>
#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

void	parse_res(t_cub *game_config, char *line)
{
	if (*line == 'R')
	{	
		line += 2;
		while (*line)
		{
			while (ft_isdigit(*line))
			{
				game_config->x_res = (game_config->x_res * 10) + (*line - '0');
				line++;
			}
			if (veirify_resolution_input(*line) == ERROR)
				ft_error(WRONG_RES);
			while (ft_isspace(*line))
				line++;
			while (ft_isdigit(*line) && game_config->x_res)
			{
				game_config->y_res = (game_config->y_res * 10) + (*line - '0');
				line++;
			}
			if (veirify_resolution_input(*line) == ERROR)
				ft_error(WRONG_RES);
		}
	}
}

void	parse_map(t_cub *game_config, char *line)
{
	t_list	*current;

	if (ft_isdigit(*line) || ft_isspace(*line) || line[0] == 0)
	{
		if (!game_config->map)
		{
			if (is_map_on_top(*game_config) && *line)
				ft_error(MAP_ON_TOP);
			if (*line)
				game_config->map = ft_lstnew(line);
			if (*line && !game_config->map)
				ft_error(MALLOC);
			return ;
		}
		current = game_config->map;
		while (current->next)
		{
			current = current->next;
		}
		current->next = ft_lstnew(line);
		if (!current->next)
			ft_error(MALLOC);
		return ;
	}
}

void	parse_type_identifiers(t_cub *game_config, char *line)
{
	if (!game_config->map)
	{
		if (ft_isalpha(*line) && is_type_identifier_allowed(line) == ERROR)
			ft_error(IDENTIFIER_ILLEGAL);
		parse_res(game_config, line);
		parse_wall_texture(game_config, line);
		parse_sprite_texture(game_config, line);
		parse_floor_colour(game_config, line);
		parse_ceiling_colour(game_config, line);
	}
}

void	parse_file(char *file, t_cub *game_config)
{
	int		fd;
	char	*line;
	int		line_status;

	fd = open(file, O_RDONLY);
	line_status = 1;
	while (line_status)
	{
		line_status = get_next_line(fd, &line);
		count_type_identifiers(game_config, line);
		parse_type_identifiers(game_config, line);
		parse_map(game_config, line);
		free(line);
	}
}
