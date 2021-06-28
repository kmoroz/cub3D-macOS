#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h> //for exit

int calculate_orientation_angle(float angle)
{
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

void	update_player_position(t_settings *settings, t_player *player)
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
