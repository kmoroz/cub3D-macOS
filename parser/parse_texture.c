#include "../cub3d.h"

int	parse_wall_texture(t_cub *game_config, char *line)
{
	char	first_char;
	char	*location;

	if (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "SO ", 3)
		|| ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "EA ", 3))
	{
		first_char = *line;
		line += 3;
		while (!ft_isspace(*line) && *line)
		{
			location = ft_strdup(line);
			if (!location)
				ft_error(MALLOC);
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
	return (OK);
}

int	parse_sprite_texture(t_cub *game_config, char *line)
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
				return (OK);
			}
		}
	}
	return (OK);
}
