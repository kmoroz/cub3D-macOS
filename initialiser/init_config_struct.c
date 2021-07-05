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
	config->map = 0;
	config->type_identifier_num = 0;
}

void	init_config(t_settings *settings, t_cub *config)
{
	settings->config = config;
}
