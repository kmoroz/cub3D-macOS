#include "../cub3d.h"
#include <stdlib.h>

void	init_player_position(t_settings *settings)
{
	float	x;
	float	y;
	int		count;
	t_list	*temp;

	temp = settings->config->map;
	x = 0;
	y = 0;
	while (temp)
	{
		count = 0;
		while ((temp->row[count]))
		{
			if (ft_strchr("NSEW", temp->row[count]))
			{
				settings->game->player->xpos = x * TILE_SIZE + TILE_SIZE / 2;
				settings->game->player->ypos = y * TILE_SIZE + TILE_SIZE / 2;
			}
			x++;
			count++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	init_player_angle(t_settings *settings)
{
	int		x;
	int		y;
	t_list	*temp;

	temp = settings->config->map;
	x = 0;
	y = 0;
	while (temp)
	{
		while ((temp->row[x]))
		{
			if (temp->row[x] == 'N')
				settings->game->player->angle = PI * 1.5;
			else if (temp->row[x] == 'W')
				settings->game->player->angle = PI;
			else if (temp->row[x] == 'E')
				settings->game->player->angle = 0;
			else if (temp->row[x] == 'S')
				settings->game->player->angle = PI * 0.5;
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	init_player(t_settings *settings)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->walk_speed = 4;
	player->turn_speed = 20 * (PI / 180);
	settings->game->player = player;
	init_player_position(settings);
	init_player_angle(settings);
}
