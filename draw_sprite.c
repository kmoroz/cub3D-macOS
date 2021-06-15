/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprite.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:31:06 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/15 16:31:18 by ksmorozo      ########   odam.nl         */
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

void	check_and_draw_sprite(t_settings *settings, float x, float y, int count, int index)
{
	int		tex_colour;
	float	texel_width;
	int		texture_offset_x;
	int		distance_from_top;
	int		texture_offset_y;

	texel_width = (settings->game->texture[index].img_width
			/ settings->game->sprite->width);
	texture_offset_x = (x - settings->game->sprite->left_x[count])
		* texel_width;
	if (x >= 0 && x < settings->config->x_res && y > 0
		&& y < settings->config->y_res)
	{	
		distance_from_top = y + (settings->game->sprite->height / 2)
			- (settings->config->y_res / 2);
		texture_offset_y = distance_from_top
			* (settings->game->texture[index].img_height
				/ settings->game->sprite->height);
		tex_colour = settings->game->texture[index]
			.colour_buffer[(settings->game->texture[index].img_width
				* texture_offset_y) + texture_offset_x];
		if (tex_colour != 16711935 && settings->game->sprite->distance[count]
			< settings->ray->distance[(int)x])
			my_mlx_pixel_put(settings->window, x, y, tex_colour);
	}
}

void	draw_sprite(t_settings *settings, int count, int index)
{
	float		x;
	float		y;

	x = settings->game->sprite->left_x[count];
	while (x < settings->game->sprite->right_x[count])
	{
		y = settings->game->sprite->top[count];
		while (y < settings->game->sprite->bottom[count])
		{
			check_and_draw_sprite(settings, x, y, count, index);
			y++;
		}
		x++;
	}
}

void	display_sprite(t_settings *settings, t_sprite *sprite, int count, int index)
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
			draw_sprite(settings, count, index);
		}
		count++;
	}
}

static void	swap_sprites(t_sprite *sprite, int i, int j)
{
	float		temp_dist;
	float		temp_y;
	float		temp_x;
	float		temp_angle;
	int			temp_visible;

	temp_dist = sprite->distance[j];
	temp_x = sprite->x[j];
	temp_y = sprite->y[j];
	temp_angle = sprite->angle[j];
	temp_visible = sprite->visible[j];
	sprite->distance[j] = sprite->distance[i];
	sprite->x[j] = sprite->x[i];
	sprite->y[j] = sprite->y[i];
	sprite->angle[j] = sprite->angle[i];
	sprite->visible[j] = sprite->visible[i];
	sprite->distance[i] = temp_dist;
	sprite->x[i] = temp_x;
	sprite->y[i] = temp_y;
	sprite->angle[i] = temp_angle;
	sprite->visible[i] = temp_visible;
}

void	sort_sprites(t_settings *settings)
{
	int	j;
	int	i;

	i = -1;
	while (i++ < settings->game->sprite->num)
	{
		j = i + 1;
		while (j < settings->game->sprite->num)
		{
			if (settings->game->sprite->distance[j]
				> settings->game->sprite->distance[i])
				swap_sprites(settings->game->sprite, i, j);
			j++;
		}
	}
}

float	calculate_angle_sprite_player
(t_settings *settings, int count, float angle_sprite_player)
{
	angle_sprite_player = settings->game->player->angle
		- atan2(settings->game->sprite->y[count]
			- settings->game->player->ypos, settings->game->sprite->x[count]
			- settings->game->player->xpos);
	if (angle_sprite_player > PI)
		angle_sprite_player -= TWO_PI;
	if (angle_sprite_player < -PI)
		angle_sprite_player += TWO_PI;
	angle_sprite_player = fabs(angle_sprite_player);
	return (angle_sprite_player);
}

void	is_sprite_visible(t_settings *settings, t_sprite *sprite, int count)
{
	float		angle_sprite_player;

	while (count < settings->game->sprite->num)
	{	
		angle_sprite_player = calculate_angle_sprite_player
			(settings, count, angle_sprite_player);
		if (angle_sprite_player < (FOV_ANGLE / 2) + EPSILON)
		{
			sprite->visible[count] = 1;
			sprite->distance[count] = calculate_distance(sprite->x[count],
					sprite->y[count], settings->game->player->xpos,
					settings->game->player->ypos);
			sprite->angle[count] = atan2(sprite->y[count]
					- settings->game->player->ypos, sprite->x[count]
					- settings->game->player->xpos)
				- settings->game->player->angle;
		}
		else
			sprite->visible[count] = 0;
		count++;
	}
}

// void animate_sprite(t_settings *settings)
// {
// 	static int	animation_offset;
// 	int	bpp;
// 	int	size_line;
// 	int	endian;

// 	if (animation_offset > 50)
// 	{
// 		settings->game->texture[SPRITE_TEXTURE].img = mlx_xpm_file_to_image(settings->window->mlx,
// 		"./textures/animation.xpm", &settings->game->texture[SPRITE_TEXTURE].img_width,
// 		&settings->game->texture[SPRITE_TEXTURE].img_height);
// 		settings->game->texture[SPRITE_TEXTURE].colour_buffer = (int *)mlx_get_data_addr(settings->game->texture[SPRITE_TEXTURE].img,
// 		&bpp, &size_line, &endian);
// 	}
// 	if (animation_offset > 100)
// 	{
// 		settings->game->texture[SPRITE_TEXTURE].img = mlx_xpm_file_to_image(settings->window->mlx,
// 		settings->config->sp_texture, &settings->game->texture[SPRITE_TEXTURE].img_width,
// 		&settings->game->texture[SPRITE_TEXTURE].img_height);
// 		settings->game->texture[SPRITE_TEXTURE].colour_buffer = (int *)mlx_get_data_addr(settings->game->texture[SPRITE_TEXTURE].img,
// 		&bpp, &size_line, &endian);
// 	}
// 	if (animation_offset > 150)
// 		animation_offset = 0;
// 	animation_offset++;
// }

void	render_sprite(t_settings *settings)
{
	t_sprite	*sprite;
	int			count;
	int			index;

	index = animate_sprite();
	sprite = settings->game->sprite;
	count = 0;
	is_sprite_visible(settings, sprite, count);
	sort_sprites(settings);
	display_sprite(settings, sprite, count, index);
}
