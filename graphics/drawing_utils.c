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

void	draw_a_square(t_window_settings *window, float x, float y, int color)
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
			my_mlx_pixel_put(window, start_x, y + count, color);
			start_x++;
			row_size--;
		}
		count++;
	}
}
