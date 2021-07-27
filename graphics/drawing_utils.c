#include "../cub3d.h"

int	get_colour(t_texture texture, int x, int y)
{
	int	colour;

	colour = *(int *)(texture.addr
			+ (y * texture.line_length)
			+ (x * texture.bits_per_pixel / 8));
	return (colour);
}

void	my_mlx_pixel_put(t_window_settings *window, int x, int y, int color)
{
	char	*dst;

	dst = window->addr + (y * window->line_length
			+ x * (window->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_a_square(t_window_settings *window, float x, float y, int colour)
{
	float	start_x;
	int		row_size;
	int		count;

	count = 0;
	while (count <= TILE_SIZE * SCALE_FACTOR)
	{
		start_x = x;
		row_size = TILE_SIZE * SCALE_FACTOR;
		while (row_size >= 0)
		{
			my_mlx_pixel_put(window, start_x, y + count, colour);
			start_x++;
			row_size--;
		}
		count++;
	}
}

void	draw_a_circle(t_window_settings *window, float x, float y, int colour)
{
	float	i;
	float	angle;
	float	x1;
	float	y1;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x1 = 1.5 * cos(angle * PI / 180);
		y1 = 1.5 * sin(angle * PI / 180);
		my_mlx_pixel_put(window, x + x1, y + y1, colour);
		i += 0.1;
	}
}

void	check_minimap_max_width_height(t_cub *config,
	int *max_width, int *max_height)
{
	t_list	*temp;

	*max_width = 0;
	*max_height = 0;
	temp = config->map;
	while (temp)
	{
		if ((int)ft_strlen(temp->row) > *max_width)
			*max_width = ft_strlen(temp->row);
		if (ft_strlen(temp->row))
			*max_height = *max_height + 1;
		temp = temp->next;
	}
	*max_width *= TILE_SIZE * SCALE_FACTOR;
	*max_height *= TILE_SIZE * SCALE_FACTOR;
}
