#include "../cub3d.h"
#include "../mlx/mlx.h"

void	draw_minimap_player(t_settings *settings)
{
	float	x;
	float	y;

	x = settings->game->player->xpos;
	y = settings->game->player->ypos;
	draw_a_circle(settings->window, x * SCALE_FACTOR,
		y * SCALE_FACTOR, 0x00464655);
}

void	draw_minimap_sprite(t_settings *settings)
{
	int	count;

	count = 0;
	while (count < settings->game->sprite->num)
	{
		draw_a_circle(settings->window,
			settings->game->sprite->x[count] * SCALE_FACTOR,
			settings->game->sprite->y[count] * SCALE_FACTOR, 0x00B7B6C1);
		count++;
	}
}

void	draw_minimap(t_settings *settings)
{
	int		x;
	int		y;
	t_list	*temp;
	int		tile_x;
	int		tile_y;

	temp = settings->config->map;
	x = 0;
	y = 0;
	while (temp)
	{
		while ((temp->row[x]))
		{
			tile_x = x * TILE_SIZE;
			tile_y = y * TILE_SIZE;
			if ((temp->row[x]) == '1')
				draw_a_square(settings->window, tile_x * SCALE_FACTOR,
					tile_y * SCALE_FACTOR, 0x00D5CFE1);
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	draw_line(t_settings *settings)
{
	double	starting_x;
	double	starting_y;
	int		line_len;
	int		counter;

	starting_x = settings->game->player->xpos * SCALE_FACTOR;
	starting_y = settings->game->player->ypos * SCALE_FACTOR;
	counter = 0;
	line_len = 10;
	while (counter <= line_len)
	{
		my_mlx_pixel_put(settings->window, starting_x, starting_y, 0x00464655);
		starting_x += cos(settings->game->player->angle);
		starting_y += sin(settings->game->player->angle);
		counter++;
	}
}

void	draw_minimap_components(t_settings *settings)
{
	int	max_width;
	int	max_height;

	check_minimap_max_width_height(settings->config, &max_width, &max_height);
	if ((settings->config->x_res >= 400 && settings->config->y_res >= 400)
		&& (settings->config->x_res > max_width
			&& settings->config->y_res > max_height))
	{
		draw_minimap_sprite(settings);
		draw_line(settings);
		draw_minimap_player(settings);
		draw_minimap(settings);
	}
}
