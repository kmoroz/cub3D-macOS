#include "../cub3d.h"

void	parse_floor_colour(t_cub *game_config, char *line)
{
	int	index;

	if (line[0] == 'F' && ft_isspace(line[1]))
	{
		line += 2;
		index = 0;
		while (line && index < 3)
		{
			while (ft_isdigit(*line) && *line != ',')
			{
				if (game_config->floor_colour[index] == -1)
					game_config->floor_colour[index] = 0;
				game_config->floor_colour[index]
					= (game_config->floor_colour[index] * 10) + (*line - '0');
				line++;
			}
			if (veirify_rgb_input(*line) == ERROR)
				ft_error(RGB_INVALID);
			index++;
			line++;
		}
	}
}

void	parse_ceiling_colour(t_cub *game_config, char *line)
{
	int	index;

	if (line[0] == 'C' && ft_isspace(line[1]))
	{
		line += 2;
		index = 0;
		while (line && index < 3)
		{
			while (ft_isdigit(*line) && *line != ',')
			{
				if (game_config->ceiling_colour[index] == -1)
					game_config->ceiling_colour[index] = 0;
				game_config->ceiling_colour[index]
					= (game_config->ceiling_colour[index] * 10) + (*line - '0');
				line++;
			}
			if (veirify_rgb_input(*line) == ERROR)
				ft_error(RGB_INVALID);
			index++;
			line++;
		}
	}
}
