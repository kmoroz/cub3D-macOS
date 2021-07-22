#include "../cub3d.h"

void	parse_east_west(t_cub *game_config, char *location, char first_char)
{
	if (first_char == 'W')
		game_config->we_texture = location;
	if (first_char == 'E')
		game_config->ea_texture = location;
}

void	parse_north_south(t_cub *game_config, char *location, char first_char)
{
	if (first_char == 'N')
		game_config->no_texture = location;
	if (first_char == 'S')
		game_config->so_texture = location;
}

void	parse_wall_texture(t_cub *game_config, char *line)
{
	char	first_char;
	char	*location;

	if (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "SO ", 3)
		|| ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "EA ", 3))
	{
		first_char = *line;
		line += 2;
		while (*line)
		{
			if (ft_isspace(*line))
				line++;
			else
			{
				location = ft_strdup(line);
				if (!location)
					ft_error(MALLOC);
				parse_east_west(game_config, location, first_char);
				parse_north_south(game_config, location, first_char);
				return ;
			}
		}
	}
}

void	parse_sprite_texture(t_cub *game_config, char *line)
{
	char	*location;

	if (ft_strnstr(line, "S ", 2))
	{
		line++;
		while (*line)
		{
			if (ft_isspace(*line))
				line++;
			else
			{
				location = ft_strdup(line);
				if (!location)
					ft_error(MALLOC);
				game_config->sp_texture = location;
				return ;
			}
		}
	}
}
