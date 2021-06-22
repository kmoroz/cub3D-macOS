#include "cub3d.h"

int	is_texture_provided(t_cub config)
{
	if (!config.ea_texture || !config.no_texture
		|| !config.so_texture || !config.we_texture
		|| !config.sp_texture)
	{
		printf("Error\n\U0001f4a9 Texture path missing \U0001f4a9\n");
		return (ERROR);
	}
	return (OK);
}
