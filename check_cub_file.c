#include "cub3d.h"

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
	if (ft_strnstr(line, "S ", 2) || ft_strnstr(line, "S\0", 2))
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
