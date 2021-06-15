/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 18:47:56 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/10 14:10:45 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h> //for exit

static void	initialise_ray_struct(t_ray *ray)
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

static int	check_wall_collision(t_settings *settings, float next_x, float next_y)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = settings->config->map;
	next_x /= TILE_SIZE;
	next_y /= TILE_SIZE;
	while (temp && count != (int)next_y)
	{
		temp = temp->next;
		count++;
	}
	if (!temp)
		return (1);
	if (temp->row[(int)next_x] == '0'
		|| ft_strchr("NSEW2", temp->row[(int)next_x]))
		return (0);
	return (1);
}

static void	find_ray_direction(t_settings *settings)
{
	if (settings->ray->ray_angle > 0 && settings->ray->ray_angle < PI)
		settings->ray->is_ray_facing_down = 1;
	else
		settings->ray->is_ray_facing_up = 1;
	if (settings->ray->ray_angle < 0.5 * PI
		|| settings->ray->ray_angle > 1.5 * PI)
		settings->ray->is_ray_facing_right = 1;
	else
		settings->ray->is_ray_facing_left = 1;
}

float	normalise_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

void look_for_walls_horizontal(t_settings *settings, float x_intercept, float y_intercept)
{
	float	next_horizontal_touch_x;
	float	next_horizontal_touch_y;
	float	tmp;

	next_horizontal_touch_x = x_intercept;
	next_horizontal_touch_y = y_intercept;
	settings->ray->horizontal_wall_hit = 0;
	tmp = 0;
	while (next_horizontal_touch_x >= 0 && next_horizontal_touch_x / TILE_SIZE <= settings->config->x_res
	&& next_horizontal_touch_y >= 0 && next_horizontal_touch_y / TILE_SIZE <= settings->config->y_res)
	{
		if (settings->ray->is_ray_facing_up)
			tmp = 1;
		if (check_wall_collision(settings, next_horizontal_touch_x, next_horizontal_touch_y - tmp))
		{
			settings->ray->horizontal_wall_hit_x = next_horizontal_touch_x;
			settings->ray->horizontal_wall_hit_y = next_horizontal_touch_y;
			settings->ray->horizontal_wall_hit = 1;
			break ;
		}
		next_horizontal_touch_x += settings->ray->hor_x_step;
		next_horizontal_touch_y += settings->ray->hor_y_step;
	}
}

void look_for_walls_vertical(t_settings *settings, float x_intercept, float y_intercept)
{
	float	next_vertical_touch_x;
	float	next_vertical_touch_y;
	float	tmp;

	next_vertical_touch_x = x_intercept;
	next_vertical_touch_y = y_intercept;
	settings->ray->vertical_wall_hit = 0;
	tmp = 0;
	while (next_vertical_touch_x >= 0 && next_vertical_touch_x / TILE_SIZE <= settings->config->x_res
	&& next_vertical_touch_y >= 0 && next_vertical_touch_y / TILE_SIZE <= settings->config->y_res)
	{
		if (settings->ray->is_ray_facing_left)
			tmp = 1;
		if (check_wall_collision(settings, next_vertical_touch_x - tmp, next_vertical_touch_y))
		{
			settings->ray->vertical_wall_hit_x = next_vertical_touch_x;
			settings->ray->vertical_wall_hit_y = next_vertical_touch_y;
			settings->ray->vertical_wall_hit = 1;
			break ;
		}
		next_vertical_touch_x += settings->ray->vert_x_step;
		next_vertical_touch_y += settings->ray->vert_y_step;
	}
}

void handle_horizontal_interception(t_settings *settings)
{
	float	x_intercept;
	float	y_intercept;

	y_intercept = floor(settings->game->player->ypos / TILE_SIZE) * TILE_SIZE;
	if (settings->ray->is_ray_facing_down)
		y_intercept += TILE_SIZE;
	x_intercept = settings->game->player->xpos + (y_intercept - settings->game->player->ypos) / tan(settings->ray->ray_angle);
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

void handle_vertical_interception(t_settings *settings)
{
	float	x_intercept;
	float	y_intercept;

	x_intercept = floor(settings->game->player->xpos / TILE_SIZE) * TILE_SIZE;
	if (settings->ray->is_ray_facing_right)
		x_intercept += TILE_SIZE;
	y_intercept = settings->game->player->ypos + (x_intercept - settings->game->player->xpos) * tan(settings->ray->ray_angle);
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

float calculate_distance(float x, float y,
	float intersection_x, float intersection_y)
{
	return (sqrt((intersection_x - x) * (intersection_x - x)
			+ (intersection_y - y) * (intersection_y - y)));
}

void find_shortest_distance(t_settings *settings, int count)
{
	float	horizontal_distance;
	float	vertical_distance;

	horizontal_distance = 0;
	vertical_distance = 0;
	if (settings->ray->horizontal_wall_hit)
		horizontal_distance = calculate_distance(settings->game->player->xpos,
				settings->game->player->ypos, settings->ray->horizontal_wall_hit_x,
				settings->ray->horizontal_wall_hit_y);
	if (settings->ray->vertical_wall_hit)
		vertical_distance = calculate_distance(settings->game->player->xpos, settings->game->player->ypos,
				settings->ray->vertical_wall_hit_x, settings->ray->vertical_wall_hit_y);
	if ((horizontal_distance < vertical_distance && horizontal_distance) || !vertical_distance)
	{
		settings->ray->wall_hit_x = settings->ray->horizontal_wall_hit_x;
		settings->ray->wall_hit_y = settings->ray->horizontal_wall_hit_y;
		settings->ray->distance[count] = horizontal_distance;
	}
	else
	{
		settings->ray->wall_hit_x = settings->ray->vertical_wall_hit_x;
		settings->ray->wall_hit_y = settings->ray->vertical_wall_hit_y;
		settings->ray->distance[count] = vertical_distance;
		settings->ray->was_hit_vertical = 1;
	}
}

void cast_rays(t_settings *settings)
{
	int		count;

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
		find_shortest_distance(settings, count);
		draw_ray(settings, settings->ray->wall_hit_x, settings->ray->wall_hit_y);
		generate_wall_projection(settings, count);
		settings->ray->ray_angle += FOV_ANGLE / settings->ray->num_rays;
		count++;
	}
}

int calculate_orientation_angle(float angle)
{
	//angle = normalise_angle(angle);
	if ((angle > PI * 0.25) && (angle < 0.75 * PI))
		return (1);
	else if ((angle > PI * 1.25) && (angle < 1.75 * PI))
		return (1);
	return (0);
}

void check_sidewalk(t_player *player, float *next_x, float *next_y, float move_step)
{
	float	side_angle;
	int		player_orientation;

	player_orientation = calculate_orientation_angle(player->angle);
	if (player->sidewalk == 1)
	{
		side_angle = (PI * 0.5) - player->angle;
		if (player_orientation == 1)
		{
			*next_x = player->xpos - cos(side_angle) * move_step;
			*next_y = player->ypos + sin(side_angle) * move_step;
		}
		else
		{
			*next_x = player->xpos + cos(side_angle) * -move_step;
			*next_y = player->ypos - sin(side_angle) * -move_step;			
		}
	}
}

static void	update_player_position(t_settings *settings, t_player *player)
{
	float	next_x;
	float	next_y;
	float	move_step;

	player->angle += player->turn_direction * player->turn_speed;
	player->angle = normalise_angle(player->angle);
	move_step = player->walk_direction * player->walk_speed;
	next_x = player->xpos + cos(player->angle) * move_step;
	next_y = player->ypos + sin(player->angle) * move_step;
	check_sidewalk(player, &next_x, &next_y, move_step);
	if (check_wall_collision(settings, next_x, next_y) == 0)
	{
		player->xpos = next_x;
		player->ypos = next_y;
	}
}

int	key_press_handler(int keycode, t_settings *settings)
{
	settings->game->player->turn_direction = 0;
	settings->game->player->walk_direction = 0;
	settings->game->player->sidewalk = 0;
	if (keycode == KEY_ESC)
		exit (0);
	else if (keycode == KEY_A)
		settings->game->player->sidewalk = 1;
	else if (keycode == KEY_D)
		settings->game->player->sidewalk = 1;
	else if (keycode == KEY_LEFT)
		settings->game->player->turn_direction = -1;
	else if (keycode == KEY_RIGHT)
		settings->game->player->turn_direction = 1;
	if (keycode == KEY_W || keycode == KEY_D)
		settings->game->player->walk_direction = 1;
	if (keycode == KEY_S || keycode == KEY_A)
		settings->game->player->walk_direction = -1;
	update_player_position(settings, settings->game->player);
	return (0);
}
