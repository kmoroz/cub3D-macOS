/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor_ceiling.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 16:35:30 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/22 13:42:48 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_floor(t_settings *settings)
{
	int	x;
	int	y;
	int	colour;

	x = 0;
	y = 0;
	colour = create_rgb(settings->config->floor_colour[0],
			settings->config->floor_colour[1],
			settings->config->floor_colour[2]);
	while (y < (settings->config->y_res / 2))
	{
		while (x < settings->config->x_res)
		{
			my_mlx_pixel_put(settings->window, x,
				y + settings->config->y_res / 2, colour);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_ceiling(t_settings *settings)
{
	int	x;
	int	y;
	int	colour;

	x = 0;
	y = 0;
	colour = create_rgb(settings->config->ceiling_colour[0],
			settings->config->ceiling_colour[1],
			settings->config->ceiling_colour[2]);
	while (y < (settings->config->y_res / 2))
	{
		while (x < settings->config->x_res)
		{
			my_mlx_pixel_put(settings->window, x, y, colour);
			x++;
		}
		x = 0;
		y++;
	}
}
