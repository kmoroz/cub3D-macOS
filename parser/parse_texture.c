#include "../cub3d.h"

int	parse_wall_texture(t_cub *game_config, char *line)
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
	return (OK);
}

int	parse_sprite_texture(t_cub *game_config, char *line)
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
	}
	return (OK);
}
