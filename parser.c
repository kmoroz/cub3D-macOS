/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:09:14 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/21 14:18:51 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stddef.h>
#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	parse_res(t_cub *game_config, char *line)
{
	if (*line == 'R')
	{
		while (*line)
		{
			while (ft_isdigit(*line))
			{
				game_config->x_res = (game_config->x_res * 10) + (*line - '0');
				line++;
			}
			while (ft_isspace(*line) || ft_isalpha(*line))
				line++;
			while (ft_isdigit(*line) && game_config->x_res)
			{
				game_config->y_res = (game_config->y_res * 10) + (*line - '0');
				line++;
			}
		}
	}
}

int	parse_texture(t_cub *game_config, char *line)
{
	char	first_char;
	char	*location;

	if (ft_strnstr(line, "NO .", 4) || ft_strnstr(line, "SO .", 4)
		|| ft_strnstr(line, "WE .", 4) || ft_strnstr(line, "EA .", 4))
	{
		first_char = *line;
		line += 3;
		while (!ft_isspace(*line))
		{
			location = ft_strdup(line);
			if (!location)
				return (ERROR);
			if (first_char == 'N')
				game_config->no_texture = location;
			if (first_char == 'S')
				game_config->so_texture = location;
			if (first_char == 'W')
				game_config->we_texture = location;
			if (first_char == 'E')
				game_config->ea_texture = location;
			return (OK);
		}
	}
}

int	parse_sprite(t_cub *game_config, char *line)
{
	char	*location;

	if (ft_strnstr(line, "S .", 3))
	{
		line += 2;
		while (!ft_isspace(*line))
		{
			location = ft_strdup(line);
			if (!location)
				return (ERROR);
			game_config->sp_texture = location;
			return (1);
		}
		return (-1);
	}
}

int	parse_floor_colour(t_cub *game_config, char *line)
{
	int	index;

	if (line[0] == 'F' && ft_isspace(line[1]))
	{
		line += 2;
		index = 0;
		if (veirify_rgb_input(*line) == ERROR)
			return (ERROR);
		while (*line && index < 3)
		{
			while (ft_isdigit(*line) && *line != ',')
			{
				game_config->floor_colour[index]
					= (game_config->floor_colour[index] * 10) + (*line - '0');
				line++;
			}
			index++;
			line++;
		}
	}
	return (OK);
}

int	parse_ceiling_colour(t_cub *game_config, char *line)
{
	int	index;

	if (line[0] == 'C' && ft_isspace(line[1]))
	{
		line += 2;
		index = 0;
		if (veirify_rgb_input(*line) == ERROR)
			return (ERROR);
		while (*line && index < 3)
		{
			while (ft_isdigit(*line) && *line != ',')
			{
				game_config->ceiling_colour[index]
					= (game_config->ceiling_colour[index] * 10) + (*line - '0');
				line++;
			}
			index++;
			line++;
		}
	}
	return (OK);
}

int	parse_map(t_cub *game_config, char *line)
{
	t_list *current;

	if (ft_isdigit(*line) || ft_isspace(*line) || line[0] == 0)
	{
		if (!game_config->map)
		{
			if (is_map_on_top(*game_config) && *line)
				return (ERROR);
			if (*line)
				game_config->map = ft_lstnew(line);
			return (OK);
		}
		current = game_config->map;
		while (current->next)
		{
			current = current->next;
		}
		current->next = ft_lstnew(line);
		printf("%s\n", line);
		return (1);
	}
}

int	parse_file(char *file, t_cub *game_config)
{
	int		fd;
	char	*line;
	int		line_status;

	fd = open(file, O_RDONLY);
	line_status = 1;
	while (line_status)
	{
		line_status = get_next_line(fd, &line);
		parse_res(game_config, line);
		parse_texture(game_config, line);
		parse_sprite(game_config, line);
		if (parse_floor_colour(game_config, line) == ERROR || parse_ceiling_colour(game_config, line) == ERROR)
		{
			printf("Error\n\U0001f4a9 Couldn't parse RGB colours. Please check the config file provided. \U0001f4a9\n");
			return (ERROR);
		}
		if (parse_map(game_config, line) == ERROR)
		{
			printf("Error\n\U0001f4a9 Couldn't parse map. Map cannot be on top of the file. \U0001f4a9\n");
			return (ERROR);
		}
		free(line);
	}
	return (OK);
}
