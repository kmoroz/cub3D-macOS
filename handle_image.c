/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_image.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 14:43:28 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/15 15:48:41 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include "libft/libft.h"

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

void	draw_minimap_player(t_settings *settings)
{
	float	x;
	float	y;

	x = settings->game->player->xpos;
	y = settings->game->player->ypos;
	my_mlx_pixel_put(settings->window, x * SCALE_FACTOR,
		y * SCALE_FACTOR, 0x00ff6e40);
	my_mlx_pixel_put(settings->window, x * SCALE_FACTOR + 1,
		y * SCALE_FACTOR, 0x00ff6e40);
	my_mlx_pixel_put(settings->window, x * SCALE_FACTOR - 1,
		y * SCALE_FACTOR, 0x00ff6e40);
}

void	draw_minimap_sprite(t_settings *settings)
{
	int	count;

	count = 0;
	while (count < settings->game->sprite->num)
	{
		my_mlx_pixel_put(settings->window, settings->game->sprite->x[count] * SCALE_FACTOR,
			settings->game->sprite->y[count] * SCALE_FACTOR, 0x00ffc13b);
		count++;
	}
}

void	draw_minimap(t_settings *settings)
{
	int	x;
	int	y;
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
				draw_a_square(settings->window, tile_x * SCALE_FACTOR, tile_y * SCALE_FACTOR, 0x00f5f0e1);
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void draw_line(t_settings *settings)
{
	double	starting_x;
	double	starting_y;
	int		line_len;
	int		counter;

	starting_x = settings->game->player->xpos * SCALE_FACTOR;
	starting_y = settings->game->player->ypos * SCALE_FACTOR;
	counter = 0;
	line_len = 20;
	while (counter <= line_len)
	{
		my_mlx_pixel_put(settings->window, starting_x, starting_y, 0x00ffc13b);
		starting_x += cos(settings->game->player->angle);
		starting_y += sin(settings->game->player->angle);
		counter++;
	}
}

void	draw_ray(t_settings *settings, float final_x, float final_y)
{
	float	starting_x;
	float	starting_y;
	float	deltaX;
	float	deltaY;
	int		pixels;

	starting_x = settings->game->player->xpos * SCALE_FACTOR;
	starting_y = settings->game->player->ypos * SCALE_FACTOR;
	deltaX = final_x * SCALE_FACTOR - starting_x;
	deltaY = final_y * SCALE_FACTOR - starting_y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
		my_mlx_pixel_put(settings->window, starting_x, starting_y, 0x001e3d59);
		starting_x += deltaX;
		starting_y += deltaY;
		--pixels;
	}
}

int	choose_texture(t_settings *settings)
{
	if (settings->ray->is_ray_facing_up && !settings->ray->was_hit_vertical)
		return (NO_TEXTURE);
	if (settings->ray->is_ray_facing_down && !settings->ray->was_hit_vertical)
		return (SO_TEXTURE);
	if (settings->ray->is_ray_facing_left && settings->ray->was_hit_vertical)
		return (WE_TEXTURE);
	if (settings->ray->is_ray_facing_right && settings->ray->was_hit_vertical)
		return (EA_TEXTURE);
	return (ERROR);
}

void	draw_wall(t_settings *settings, int count)
{
	int	texture_offset_x;
	int	index;
	int	distance_from_top;
	int	texture_offset_y;
	int	tex_colour;

	index = choose_texture(settings);
	if (settings->ray->was_hit_vertical)
		texture_offset_x = (int)(settings->ray->wall_hit_y * settings->game->texture[index].img_width
				/ TILE_SIZE) % settings->game->texture[index].img_width;
	else
		texture_offset_x = (int)(settings->ray->wall_hit_x * settings->game->texture[index].img_width
				/ TILE_SIZE) % settings->game->texture[index].img_width;
	while (settings->game->wall->wall_top_pixel < settings->game->wall->wall_bottom_pixel)
	{
		distance_from_top = settings->game->wall->wall_top_pixel + (settings->game->wall->wall_strip_height / 2) - (settings->config->y_res / 2);
		texture_offset_y = distance_from_top * ((float)settings->game->texture[index].img_height / settings->game->wall->wall_strip_height);
		tex_colour = settings->game->texture[index].colour_buffer[(settings->game->texture[index].img_width * texture_offset_y) + texture_offset_x];
		my_mlx_pixel_put(settings->window, count, settings->game->wall->wall_top_pixel, tex_colour);
		//settings->window->colour_buffer[(settings->config->x_res * settings->game->wall->wall_top_pixel) + count] = tex_colour; //0x00FF0000
		settings->game->wall->wall_top_pixel++;
	}
}

void	generate_wall_projection(t_settings *settings, int count)
{
	float	correct_distance;

	correct_distance = settings->ray->distance[count] * cos(settings->ray->ray_angle - settings->game->player->angle);
	settings->game->wall->proj_plane_distance = (settings->config->x_res / 2) / tan(FOV_ANGLE / 2);
	settings->game->wall->wall_height = (TILE_SIZE / correct_distance) * settings->game->wall->proj_plane_distance;
	settings->game->wall->wall_strip_height = (int)settings->game->wall->wall_height;
	settings->game->wall->wall_top_pixel = (settings->config->y_res / 2) - (settings->game->wall->wall_strip_height / 2);
	if (settings->game->wall->wall_top_pixel < 0)
		settings->game->wall->wall_top_pixel = 0;
	settings->game->wall->wall_bottom_pixel = (settings->config->y_res / 2) + (settings->game->wall->wall_strip_height / 2);
	if (settings->game->wall->wall_bottom_pixel > settings->config->y_res)
		settings->game->wall->wall_bottom_pixel = settings->config->y_res;
	draw_wall(settings, count);
}

void	create_image(t_settings *settings)
{
	settings->window->img = mlx_new_image(settings->window->mlx, settings->config->x_res, settings->config->y_res);
	settings->window->addr = (int *)mlx_get_data_addr(settings->window->img,
			&settings->window->bits_per_pixel, &settings->window->line_length,
			&settings->window->endian);
}

int	refresh(t_settings *settings)
{
	create_image(settings);
	draw_floor(settings);
	draw_ceiling(settings);
	draw_line(settings);
	cast_rays(settings);
	render_sprite(settings);
	draw_line(settings);
	draw_minimap(settings);
	draw_minimap_player(settings);
	draw_minimap_sprite(settings);
	mlx_put_image_to_window(settings->window->mlx,
		settings->window->window, settings->window->img, 0, 0);
	mlx_destroy_image(settings->window->mlx, settings->window->img);
	return (0);
}
