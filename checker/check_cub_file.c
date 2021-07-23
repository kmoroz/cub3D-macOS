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
	if (ft_strnstr(line, "F", 1))
		config->type_identifier_num++;
	if (ft_strnstr(line, "C", 1))
		config->type_identifier_num++;
}

int	is_type_identifier_allowed(char *line)
{
	if (ft_strnstr(line, "NO", 2) || ft_strnstr(line, "SO", 2)
		|| ft_strnstr(line, "EA", 2) || ft_strnstr(line, "WE", 2)
		|| ft_strnstr(line, "S ", 2) || ft_strnstr(line, "F", 1)
		|| ft_strnstr(line, "C", 1) || ft_strnstr(line, "R", 1))
		return (OK);
	return (ERROR);
}

void	verify_num_of_type_identifiers(t_cub config)
{
	if (config.type_identifier_num < TYPE_IDENTIFIERS)
		ft_error(IDENTIFIERS);
	if (config.type_identifier_num > TYPE_IDENTIFIERS)
		ft_error(IDENTIFIERS);
}

void	check_config_file(t_cub config)
{
	verify_num_of_type_identifiers(config);
	check_map(config);
	check_player(config);
	check_max_rgb_value(config);
	check_resolution(&config);
	contains_sprites(&config);
	is_texture_provided(config);
	is_rgb_present(config);
	does_file_exist(config);
}
