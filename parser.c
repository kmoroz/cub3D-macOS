/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:09:14 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/09 17:08:18 by ksmorozo      ########   odam.nl         */
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
	return (1);
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
		if (!*line)
			return (1);
		game_config->map = ft_lstnew(line);
		return (1);
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

t_cub	parse_file(char *file)
{
	t_cub	game_config;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	ft_memset(&game_config, 0, sizeof(game_config));
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'R')
			parse_res(&game_config, line);
		if (line[0] == 'N' && line[1] == 'O')
			parse_texture(&game_config, line);
		if (line[0] == 'S' && line[1] == 'O')
			parse_texture(&game_config, line);
		if (line[0] == 'W' && line[1] == 'E')
			parse_texture(&game_config, line);
		if (line[0] == 'E' && line[1] == 'A')
			parse_texture(&game_config, line);
		if (line[0] == 'S' && ft_isspace(line[1]))
			parse_sprite(&game_config, line);
		if (line[0] == 'F' && ft_isspace(line[1]))
			parse_floor_colour(&game_config, line);
		if (line[0] == 'C' && ft_isspace(line[1]))
			parse_ceiling_colour(&game_config, line);
		if (ft_isdigit(*line) || ft_isspace(*line) || line[0] == 0)
			parse_map(&game_config, line);
		// free(line);
	}
	parse_map(&game_config, line);
	//free(line);
	return (game_config);
}
