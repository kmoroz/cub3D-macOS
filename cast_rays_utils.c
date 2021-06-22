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

void	find_shortest_distance(t_player *player, t_ray *ray, int count)
{
	float	hor_distance;
	float	vert_distance;

	hor_distance = 0;
	vert_distance = 0;
	if (ray->horizontal_wall_hit)
		hor_distance = calculate_distance(player->xpos,
				player->ypos, ray->horizontal_wall_hit_x,
				ray->horizontal_wall_hit_y);
	if (ray->vertical_wall_hit)
		vert_distance = calculate_distance(player->xpos, player->ypos,
				ray->vertical_wall_hit_x, ray->vertical_wall_hit_y);
	if ((hor_distance < vert_distance && hor_distance) || !vert_distance)
	{
		ray->wall_hit_x = ray->horizontal_wall_hit_x;
		ray->wall_hit_y = ray->horizontal_wall_hit_y;
		ray->distance[count] = hor_distance;
	}
	else
	{
		ray->wall_hit_x = ray->vertical_wall_hit_x;
		ray->wall_hit_y = ray->vertical_wall_hit_y;
		ray->distance[count] = vert_distance;
		ray->was_hit_vertical = 1;
	}
}
