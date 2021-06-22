#include "cub3d.h"

void	swap_sprites(t_sprite *sprite, int i, int j)
{
	float		temp_dist;
	float		temp_y;
	float		temp_x;
	float		temp_angle;
	int			temp_visible;

	temp_dist = sprite->distance[j];
	temp_x = sprite->x[j];
	temp_y = sprite->y[j];
	temp_angle = sprite->angle[j];
	temp_visible = sprite->visible[j];
	sprite->distance[j] = sprite->distance[i];
	sprite->x[j] = sprite->x[i];
	sprite->y[j] = sprite->y[i];
	sprite->angle[j] = sprite->angle[i];
	sprite->visible[j] = sprite->visible[i];
	sprite->distance[i] = temp_dist;
	sprite->x[i] = temp_x;
	sprite->y[i] = temp_y;
	sprite->angle[i] = temp_angle;
	sprite->visible[i] = temp_visible;
}

void	sort_sprites(t_settings *settings)
{
	int	j;
	int	i;

	i = -1;
	while (i++ < settings->game->sprite->num)
	{
		j = i + 1;
		while (j < settings->game->sprite->num)
		{
			if (settings->game->sprite->distance[j]
				> settings->game->sprite->distance[i])
				swap_sprites(settings->game->sprite, i, j);
			j++;
		}
	}
}

float	calculate_angle_sprite_player(t_settings *settings,
	int count, float angle_sprite_player)
{
	angle_sprite_player = settings->game->player->angle
		- atan2(settings->game->sprite->y[count]
			- settings->game->player->ypos, settings->game->sprite->x[count]
			- settings->game->player->xpos);
	if (angle_sprite_player > PI)
		angle_sprite_player -= TWO_PI;
	if (angle_sprite_player < -PI)
		angle_sprite_player += TWO_PI;
	angle_sprite_player = fabs(angle_sprite_player);
	return (angle_sprite_player);
}

void	is_sprite_visible(t_settings *settings, t_sprite *sprite, int count)
{
	float		angle_sprite_player;

	while (count < settings->game->sprite->num)
	{	
		angle_sprite_player = calculate_angle_sprite_player
			(settings, count, angle_sprite_player);
		if (angle_sprite_player < (FOV_ANGLE / 2) + EPSILON)
		{
			sprite->visible[count] = 1;
			sprite->distance[count] = calculate_distance(sprite->x[count],
					sprite->y[count], settings->game->player->xpos,
					settings->game->player->ypos);
			sprite->angle[count] = atan2(sprite->y[count]
					- settings->game->player->ypos, sprite->x[count]
					- settings->game->player->xpos)
				- settings->game->player->angle;
		}
		else
			sprite->visible[count] = 0;
		count++;
	}
}
