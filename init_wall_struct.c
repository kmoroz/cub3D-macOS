#include "cub3d.h"
#include <stdlib.h>

void	init_wall(t_settings *settings)
{
	t_wall	*wall;

	wall = malloc(sizeof(t_wall));
	settings->game->wall = wall;
	wall->wall_top_pixel = 0;
	wall->wall_strip_height = 0;
	wall->wall_height = 0;
	wall->wall_bottom_pixel = 0;
	wall->proj_plane_distance = 0;
}
