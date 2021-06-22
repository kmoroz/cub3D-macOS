#include "cub3d.h"
#include "libft/libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h> //for exit

void	look_for_walls_horizontal(t_settings *settings,
	float x_intercept, float y_intercept)
{
	float	next_hor_touch_x;
	float	next_hor_touch_y;
	float	tmp;

	next_hor_touch_x = x_intercept;
	next_hor_touch_y = y_intercept;
	settings->ray->horizontal_wall_hit = 0;
	tmp = 0;
	while (next_hor_touch_x >= 0 && next_hor_touch_x / TILE_SIZE
		<= settings->config->x_res && next_hor_touch_y >= 0
		&& next_hor_touch_y / TILE_SIZE <= settings->config->y_res)
	{
		if (settings->ray->is_ray_facing_up)
			tmp = 1;
		if (check_wall_collision(settings, next_hor_touch_x,
				next_hor_touch_y - tmp))
		{
			settings->ray->horizontal_wall_hit_x = next_hor_touch_x;
			settings->ray->horizontal_wall_hit_y = next_hor_touch_y;
			settings->ray->horizontal_wall_hit = 1;
			break ;
		}
		next_hor_touch_x += settings->ray->hor_x_step;
		next_hor_touch_y += settings->ray->hor_y_step;
	}
}

void	look_for_walls_vertical(t_settings *settings,
	float x_intercept, float y_intercept)
{
	float	next_vert_touch_x;
	float	next_vert_touch_y;
	float	tmp;

	next_vert_touch_x = x_intercept;
	next_vert_touch_y = y_intercept;
	settings->ray->vertical_wall_hit = 0;
	tmp = 0;
	while (next_vert_touch_x >= 0 && next_vert_touch_x / TILE_SIZE
		<= settings->config->x_res && next_vert_touch_y >= 0
		&& next_vert_touch_y / TILE_SIZE <= settings->config->y_res)
	{
		if (settings->ray->is_ray_facing_left)
			tmp = 1;
		if (check_wall_collision(settings,
				next_vert_touch_x - tmp, next_vert_touch_y))
		{
			settings->ray->vertical_wall_hit_x = next_vert_touch_x;
			settings->ray->vertical_wall_hit_y = next_vert_touch_y;
			settings->ray->vertical_wall_hit = 1;
			break ;
		}
		next_vert_touch_x += settings->ray->vert_x_step;
		next_vert_touch_y += settings->ray->vert_y_step;
	}
}

void	handle_horizontal_interception(t_settings *settings)
{
	float	x_intercept;
	float	y_intercept;
	t_ray	*ray;

	y_intercept = floor(settings->game->player->ypos / TILE_SIZE) * TILE_SIZE;
	if (settings->ray->is_ray_facing_down)
		y_intercept += TILE_SIZE;
	x_intercept = settings->game->player->xpos
		+ (y_intercept - settings->game->player->ypos)
		/ tan(settings->ray->ray_angle);
	settings->ray->hor_y_step = TILE_SIZE;
	if (settings->ray->is_ray_facing_up)
		settings->ray->hor_y_step *= -1;
	settings->ray->hor_x_step = TILE_SIZE / tan(settings->ray->ray_angle);
	if (settings->ray->is_ray_facing_left && settings->ray->hor_x_step > 0)
		settings->ray->hor_x_step *= -1;
	if (settings->ray->is_ray_facing_right && settings->ray->hor_x_step < 0)
		settings->ray->hor_x_step *= -1;
	look_for_walls_horizontal(settings, x_intercept, y_intercept);
}

void	handle_vertical_interception(t_settings *settings)
{
	float	x_intercept;
	float	y_intercept;

	x_intercept = floor(settings->game->player->xpos / TILE_SIZE) * TILE_SIZE;
	if (settings->ray->is_ray_facing_right)
		x_intercept += TILE_SIZE;
	y_intercept = settings->game->player->ypos
		+ (x_intercept - settings->game->player->xpos)
		* tan(settings->ray->ray_angle);
	settings->ray->vert_x_step = TILE_SIZE;
	if (settings->ray->is_ray_facing_left)
		settings->ray->vert_x_step *= -1;
	settings->ray->vert_y_step = TILE_SIZE * tan(settings->ray->ray_angle);
	if (settings->ray->is_ray_facing_up && settings->ray->vert_y_step > 0)
		settings->ray->vert_y_step *= -1;
	if (settings->ray->is_ray_facing_down && settings->ray->vert_y_step < 0)
		settings->ray->vert_y_step *= -1;
	look_for_walls_vertical(settings, x_intercept, y_intercept);
}

void	cast_rays(t_settings *settings)
{
	int			count;
	t_ray		*ray;
	t_player	*player;

	ray = settings->ray;
	player = settings->game->player;
	settings->ray->num_rays = settings->config->x_res;
	settings->ray->ray_angle = settings->game->player->angle - (FOV_ANGLE / 2);
	count = 0;
	while (count < settings->ray->num_rays)
	{
		settings->ray->ray_angle = normalise_angle(settings->ray->ray_angle);
		initialise_ray_struct(settings->ray);
		find_ray_direction(settings);
		handle_horizontal_interception(settings);
		handle_vertical_interception(settings);
		find_shortest_distance(player, ray, count);
		draw_ray(settings, settings->ray->wall_hit_x,
			settings->ray->wall_hit_y);
		generate_wall_projection(settings, count);
		settings->ray->ray_angle += FOV_ANGLE / settings->ray->num_rays;
		count++;
	}
}
