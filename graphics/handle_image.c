/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_image.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 14:43:28 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/26 15:14:24 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include "../libft/libft.h"

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
	return (ERROR); //remove
}

void	draw_wall(t_settings *settings, t_texture texture, int count)
{
	int	texture_offset_x;
	int	distance_from_top;
	int	texture_offset_y;
	int	tex_colour;

	if (settings->ray->was_hit_vertical)
		texture_offset_x = (int)(settings->ray->wall_hit_y
				* texture.img_width / TILE_SIZE) % texture.img_width;
	else
		texture_offset_x = (int)(settings->ray->wall_hit_x
				* texture.img_width / TILE_SIZE) % texture.img_width;
	while (settings->game->wall->wall_top_pixel
		< settings->game->wall->wall_bottom_pixel)
	{
		distance_from_top = settings->game->wall->wall_top_pixel
			+ (settings->game->wall->wall_strip_height / 2)
			- (settings->config->y_res / 2);
		texture_offset_y = distance_from_top * ((float)texture.img_height
				/ settings->game->wall->wall_strip_height);
		tex_colour = get_colour(texture, texture_offset_x, texture_offset_y);
		my_mlx_pixel_put(settings->window, count,
			settings->game->wall->wall_top_pixel, tex_colour);
		settings->game->wall->wall_top_pixel++;
	}
}

void	generate_wall_projection(t_settings *settings, int count)
{
	float		correct_distance;
	int			index;
	t_texture	texture;

	index = choose_texture(settings);
	texture = settings->game->texture[index];
	correct_distance = settings->ray->distance[count]
		* cos(settings->ray->ray_angle
			- settings->game->player->angle);
	settings->game->wall->proj_plane_distance = (settings->config->x_res / 2)
		/ tan(FOV_ANGLE / 2);
	settings->game->wall->wall_height = (TILE_SIZE / correct_distance)
		* settings->game->wall->proj_plane_distance;
	settings->game->wall->wall_strip_height
		= (int)settings->game->wall->wall_height;
	settings->game->wall->wall_top_pixel = (settings->config->y_res / 2)
		- (settings->game->wall->wall_strip_height / 2);
	if (settings->game->wall->wall_top_pixel < 0)
		settings->game->wall->wall_top_pixel = 0;
	settings->game->wall->wall_bottom_pixel = (settings->config->y_res / 2)
		+ (settings->game->wall->wall_strip_height / 2);
	if (settings->game->wall->wall_bottom_pixel > settings->config->y_res)
		settings->game->wall->wall_bottom_pixel = settings->config->y_res;
	draw_wall(settings, texture, count);
}

void	create_image(t_settings *settings)
{
	settings->window->img = mlx_new_image(settings->window->mlx,
			settings->config->x_res, settings->config->y_res);
	settings->window->addr = (int *)mlx_get_data_addr(settings->window->img,
			&settings->window->bits_per_pixel, &settings->window->line_length,
			&settings->window->endian);
}

int	refresh(t_settings *settings)
{
	create_image(settings);
	draw_floor(settings);
	draw_ceiling(settings);
	cast_rays(settings);
	render_sprite(settings);
	draw_minimap_components(settings);
	mlx_put_image_to_window(settings->window->mlx,
		settings->window->window, settings->window->img, 0, 0);
	mlx_destroy_image(settings->window->mlx, settings->window->img);
	return (0);
}
