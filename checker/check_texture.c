#include "../cub3d.h"
#include <stdio.h>

void	is_texture_provided(t_cub config)
{
	if (!config.ea_texture || !config.no_texture
		|| !config.so_texture || !config.we_texture
		|| !config.sp_texture)
		ft_error(ZERO_TEXTURE);
}

void	check_east_west(t_cub config)
{
	FILE	*file;

	file = fopen(config.ea_texture, "r");
	if (file)
		fclose(file);
	else
		ft_error(FILE_MISSING);
	file = fopen(config.we_texture, "r");
	if (file)
		fclose(file);
	else
		ft_error(FILE_MISSING);
}

void	check_north_south(t_cub config)
{
	FILE	*file;

	file = fopen(config.no_texture, "r");
	if (file)
		fclose(file);
	else
		ft_error(FILE_MISSING);
	file = fopen(config.so_texture, "r");
	if (file)
		fclose(file);
	else
		ft_error(FILE_MISSING);
}

void	check_sprite(t_cub config)
{
	FILE	*file;

	file = fopen(config.sp_texture, "r");
	if (file)
		fclose(file);
	else
		ft_error(FILE_MISSING);
}

void	does_file_exist(t_cub config)
{
	check_east_west(config);
	check_north_south(config);
	check_sprite(config);
}
