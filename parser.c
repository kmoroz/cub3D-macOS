/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:09:14 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/19 17:00:44 by ksmorozo      ########   odam.nl         */
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
	if (game_config->x_res && game_config->y_res)
	{
		printf("Resolution was parsed successfully!\n");
		return (1);
	}
	else
	{
		printf("Resolution parsing error!\n");
		return (-1);
	}
}

int	parse_texture(t_cub *game_config, char *line)
{
	char	first_char;
	char	*location;

	first_char = *line;
	line += 3;
	while (!ft_isspace(*line))
	{
		location = ft_strdup(line);
		if (!location)
			return (-1);
		if (first_char == 'N')
			game_config->no_texture = location;
		if (first_char == 'S')
			game_config->so_texture = location;
		if (first_char == 'W')
			game_config->we_texture = location;
		if (first_char == 'E')
			game_config->ea_texture = location;
		return (1);
	}
	printf("Texture parsing error!\n");
	return (-1);
}

int	parse_sprite(t_cub *game_config, char *line)
{
	char	*location;

	line += 2;
	while (!ft_isspace(*line))
	{
		location = ft_strdup(line);
		if (!location)
			return (-1);
		game_config->sp_texture = location;
		return (1);
	}
	printf("Sprite parsing error!\n");
	return (-1);
}

int	parse_floor_colour(t_cub *game_config, char *line)
{
	int	index;

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
	return (OK);
}

int	parse_ceiling_colour(t_cub *game_config, char *line)
{
	int	index;

	line += 2;
	index = 0;
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
	return (1);
}

int	parse_map(t_cub *game_config, char *line)
{
	t_list *current;

	if (!game_config->map)
	{
		if (!game_config->no_texture || !game_config->so_texture || !game_config->x_res || !game_config->y_res)
			return (ERROR);
		if (line[0] != '\0')
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
	return (OK);
}

int	parse_file(char *file, t_cub *game_config)
{
	int		fd;
	char	*line;
	int		result;
	int		line_status;

	fd = open(file, O_RDONLY);
	result = 1;
	line_status = 1;
	while (line_status == OK && result == OK)
	{
		line_status = get_next_line(fd, &line);
		if (*line == 'R')
			result = parse_res(game_config, line);
		if (line[0] == 'N' && line[1] == 'O')
			result = parse_texture(game_config, line);
		if (line[0] == 'S' && line[1] == 'O')
			result = parse_texture(game_config, line);
		if (line[0] == 'W' && line[1] == 'E')
			result = parse_texture(game_config, line);
		if (line[0] == 'E' && line[1] == 'A')
			result = parse_texture(game_config, line);
		if (line[0] == 'S' && ft_isspace(line[1]))
			result = parse_sprite(game_config, line);
		if (line[0] == 'F' && ft_isspace(line[1]))
			result = parse_floor_colour(game_config, line);
		if (line[0] == 'C' && ft_isspace(line[1]))
			result = parse_ceiling_colour(game_config, line);
		if (ft_isdigit(line[0]) || ft_isspace(line[0]) || line[0] == 0)
			result = parse_map(game_config, line);
		free(line);
	}
	return (result);
}
