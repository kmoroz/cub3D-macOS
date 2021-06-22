/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprite.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:31:06 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/22 14:14:29 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"

int	animate_sprite(void)
{
	static int	animation_offset;

	if (animation_offset >= 0 && animation_offset < 50)
	{
		animation_offset++;
		return (SPRITE_TEXTURE);
	}
	if (animation_offset >= 50 && animation_offset < 100)
	{
		animation_offset++;
		return (ANIMATION_TEX);
	}
	if (animation_offset >= 100 && animation_offset < 150)
	{
		animation_offset++;
		return (SPRITE_TEXTURE);
	}
	if (animation_offset >= 150)
	{
		animation_offset = 0;
		return (SPRITE_TEXTURE);
	}
	animation_offset++;
}

void	check_and_draw_sprite(t_settings *settings, float x, float y, int count)
{
	int		tex_colour;
	float	texel_width;
	int		texture_offset_x;
	int		distance_from_top;
	int		texture_offset_y;

	texel_width = (settings->game->texture[settings->game
			->sprite->animation_index].img_width
			/ settings->game->sprite->width);
	texture_offset_x = (x - settings->game->sprite->left_x[count])
		* texel_width;
	if (x >= 0 && x < settings->config->x_res && y > 0
		&& y < settings->config->y_res)
	{	
		distance_from_top = y + (settings->game->sprite->height / 2)
			- (settings->config->y_res / 2);
		texture_offset_y = distance_from_top * (settings->game->texture
			[settings->game->sprite->animation_index].img_height
				/ settings->game->sprite->height);
		tex_colour = get_colour(settings->game->texture[settings->game
				->sprite->animation_index], texture_offset_x, texture_offset_y);
		if (tex_colour != 16711935 && settings->game->sprite->distance[count]
			< settings->ray->distance[(int)x])
			my_mlx_pixel_put(settings->window, x, y, tex_colour);
	}
}

void	draw_sprite(t_settings *settings, int count)
{
	float		x;
	float		y;

	x = settings->game->sprite->left_x[count];
	while (x < settings->game->sprite->right_x[count])
	{
		y = settings->game->sprite->top[count];
		while (y < settings->game->sprite->bottom[count])
		{
			check_and_draw_sprite(settings, x, y, count);
			y++;
		}
		x++;
	}
}

void	display_sprite(t_settings *settings, t_sprite *sprite, int count)
{
	while (count < sprite->num)
	{
		if (sprite->visible[count] == 1)
		{
			sprite = settings->game->sprite;
			sprite->height = ((float)TILE_SIZE / sprite->distance[count])
				* settings->game->wall->proj_plane_distance;
			sprite->width = sprite->height;
			sprite->top[count] = (settings->config->y_res / 2)
				- (sprite->height / 2);
			if (sprite->top[count] < 0)
				sprite->top[count] = 0;
			sprite->bottom[count] = (settings->config->y_res / 2)
				+ (sprite->height / 2);
			if (sprite->bottom[count] > settings->config->y_res)
				sprite->bottom[count] = settings->config->y_res;
			sprite->screen_pos_x[count] = tan(sprite->angle[count])
				* settings->game->wall->proj_plane_distance;
			sprite->left_x[count] = (settings->config->x_res / 2)
				+ sprite->screen_pos_x[count] - (sprite->width / 2);
			sprite->right_x[count] = sprite->left_x[count] + sprite->width;
			draw_sprite(settings, count);
		}
		count++;
	}
}

void	render_sprite(t_settings *settings)
{
	t_sprite	*sprite;
	int			count;

	sprite = settings->game->sprite;
	count = 0;
	sprite->animation_index = animate_sprite();
	is_sprite_visible(settings, sprite, count);
	sort_sprites(settings);
	display_sprite(settings, sprite, count);
}
