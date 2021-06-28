#include "../cub3d.h"
#include <stdio.h>

void	count_type_identifiers(t_cub *config, char *line)
{
	if (ft_strnstr(line, "NO", 2))
		config->type_identifier_num++;
	if (ft_strnstr(line, "SO", 2))
		config->type_identifier_num++;
	if (ft_strnstr(line, "EA", 2))
		config->type_identifier_num++;
	if (ft_strnstr(line, "WE", 2))
		config->type_identifier_num++;
	if (ft_strnstr(line, "S ", 2) || (ft_strnstr(line, "S", 1)
			&& !ft_strnstr(line, "SO", 2)))
		config->type_identifier_num++;
	if (ft_strnstr(line, "F", 1))
		config->type_identifier_num++;
	if (ft_strnstr(line, "C", 1))
		config->type_identifier_num++;
	if (ft_strnstr(line, "R", 1))
		config->type_identifier_num++;
}

int	verify_num_of_type_identifiers(t_cub config)
{
	if (config.type_identifier_num < 8)
	{
		printf("Error\n\U0001f4a9 Type identifier missing \U0001f4a9\n");
		return (ERROR);
	}
	if (config.type_identifier_num > 8)
	{
		printf("Error\n\U0001f4a9 Too many type identifiers \U0001f4a9\n");
		return (ERROR);
	}
	else
		return (OK);
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
	if (check_max_rgb_value(config) == ERROR)
		return (ERROR);
	if (config.x_res == 0 || config.y_res == 0)
	{
		printf("Error\n\U0001f4a9 Resolution cannot be zero \U0001f4a9\n");
		return (ERROR);
	}
	if (is_texture_provided(config) == ERROR)
		return (ERROR);
	if (verify_num_of_type_identifiers(config) == ERROR)
		return (ERROR);
	if (is_rgb_present(config) == ERROR)
		return (ERROR);
	return (OK);
}
