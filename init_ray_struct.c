#include "cub3d.h"
#include <stdlib.h>

void	reset_ray_struct(t_ray *ray)
{
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->vertical_wall_hit_x = 0;
	ray->vertical_wall_hit_y = 0;
	ray->horizontal_wall_hit_x = 0;
	ray->horizontal_wall_hit_y = 0;
	ray->vertical_wall_hit = 0;
	ray->horizontal_wall_hit = 0;
	ray->is_ray_facing_down = 0;
	ray->is_ray_facing_up = 0;
	ray->is_ray_facing_right = 0;
	ray->is_ray_facing_left = 0;
	ray->hor_x_step = 0;
	ray->hor_y_step = 0;
	ray->vert_x_step = 0;
	ray->vert_y_step = 0;
	ray->was_hit_vertical = 0;
}

void	init_ray(t_settings *settings)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->ray_angle = 0;
	ray->vertical_wall_hit_x = 0;
	ray->vertical_wall_hit_y = 0;
	ray->horizontal_wall_hit_x = 0;
	ray->horizontal_wall_hit_y = 0;
	ray->was_hit_vertical = 0;
	ray->distance = malloc(sizeof(float) * settings->config->x_res);
	settings->ray = ray;
}
