#include "cub3d.h"

float	calculate_distance(float x, float y,
	float intersection_x, float intersection_y)
{
	return (sqrt((intersection_x - x) * (intersection_x - x)
			+ (intersection_y - y) * (intersection_y - y)));
}

float	normalise_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

int	check_wall_collision(t_settings *settings, float next_x, float next_y)
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

void	find_ray_direction(t_settings *settings)
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
