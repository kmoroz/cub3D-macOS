#include "../cub3d.h"
#include <stdlib.h>

void	init_texture_path(t_cub *config)
{
	config->ea_texture = 0;
	config->so_texture = 0;
	config->sp_texture = 0;
	config->we_texture = 0;
	config->no_texture = 0;
	config->x_res = '\0';
	config->y_res = '\0';
	config->floor_colour[0] = -1;
	config->floor_colour[1] = -1;
	config->floor_colour[2] = -1;
	config->ceiling_colour[0] = -1;
	config->ceiling_colour[1] = -1;
	config->ceiling_colour[2] = -1;
}

void	init_config(t_settings *settings, t_cub *config)
{
	settings->config = malloc(sizeof(t_cub));
	if (!settings->config)
		ft_error(MALLOC);
	settings->config = config;
}
