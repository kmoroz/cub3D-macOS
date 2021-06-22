#include "cub3d.h"

int	get_colour(t_texture texture, int x, int y)
{
	int	colour;

	colour = *(int *)(texture.addr
			+ (y * texture.line_length)
			+ (x * texture.bits_per_pixel / 8));
	return (colour);
}
