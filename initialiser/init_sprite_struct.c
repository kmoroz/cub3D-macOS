#include "../cub3d.h"
#include <stdlib.h>

void	count_sprites(t_settings *settings)
{
	int		x;
	int		y;
	t_list	*temp;

	temp = settings->config->map;
	settings->game->sprite->num = 0;
	x = 0;
	y = 0;
	while (temp)
	{
		while ((temp->row[x]))
		{
			if (temp->row[x] == '2')
				settings->game->sprite->num++;
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	init_sprite_position(t_settings *settings, t_sprite *sprite)
{
	int		x;
	int		y;
	int		count;
	t_list	*temp;

	temp = settings->config->map;
	x = 0;
	y = 0;
	count = 0;
	while (temp)
	{
		while ((temp->row[x]))
		{
			if (temp->row[x] == '2')
			{
				sprite->x[count] = x * TILE_SIZE + TILE_SIZE / 2;
				sprite->y[count] = y * TILE_SIZE + TILE_SIZE / 2;
				count++;
			}
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	init_sprite(t_settings *settings)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		ft_error(MALLOC);
	settings->game->sprite = sprite;
	count_sprites(settings);
	sprite->x = malloc(sizeof(float) * sprite->num);
	sprite->y = malloc(sizeof(float) * sprite->num);
	sprite->distance = malloc(sizeof(float) * sprite->num);
	sprite->visible = malloc(sizeof(int) * sprite->num);
	sprite->angle = malloc(sizeof(float) * sprite->num);
	sprite->top = malloc(sizeof(float) * sprite->num);
	sprite->bottom = malloc(sizeof(float) * sprite->num);
	sprite->screen_pos_x = malloc(sizeof(float) * sprite->num);
	sprite->right_x = malloc(sizeof(float) * sprite->num);
	sprite->left_x = malloc(sizeof(float) * sprite->num);
	if (!sprite->x || !sprite->y || !sprite->distance || !sprite->visible
		|| !sprite->angle || !sprite->top || !sprite->bottom
		|| !sprite->screen_pos_x || !sprite->right_x
		|| !sprite->left_x)
		ft_error(MALLOC);
	init_sprite_position(settings, sprite);
}
