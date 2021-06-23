/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 11:49:57 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/23 11:59:24 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"

void	load_sprite_texture(t_settings *settings)
{
	settings->game->texture[SPRITE_TEXTURE].img
		= mlx_xpm_file_to_image(settings->window->mlx,
			settings->config->sp_texture,
			&settings->game->texture[SPRITE_TEXTURE].img_width,
			&settings->game->texture[SPRITE_TEXTURE].img_height);
	settings->game->texture[SPRITE_TEXTURE].addr
		= mlx_get_data_addr(settings->game->texture[SPRITE_TEXTURE].img,
			&settings->game->texture[SPRITE_TEXTURE].bits_per_pixel,
			&settings->game->texture[SPRITE_TEXTURE].line_length,
			&settings->game->texture[SPRITE_TEXTURE].endian);
	settings->game->texture[ANIMATION_TEX].img
		= mlx_xpm_file_to_image(settings->window->mlx,
			"./textures/animation.xpm",
			&settings->game->texture[ANIMATION_TEX].img_width,
			&settings->game->texture[ANIMATION_TEX].img_height);
	settings->game->texture[ANIMATION_TEX].addr
		= mlx_get_data_addr(settings->game->texture[ANIMATION_TEX].img,
			&settings->game->texture[ANIMATION_TEX].bits_per_pixel,
			&settings->game->texture[ANIMATION_TEX].line_length,
			&settings->game->texture[ANIMATION_TEX].endian);
}

void	load_north_south_texture(t_settings *settings)
{
	settings->game->texture[NO_TEXTURE].img
		= mlx_xpm_file_to_image(settings->window->mlx,
			settings->config->no_texture,
			&settings->game->texture[NO_TEXTURE].img_width,
			&settings->game->texture[NO_TEXTURE].img_height);
	settings->game->texture[NO_TEXTURE].addr
		= mlx_get_data_addr(settings->game->texture[NO_TEXTURE].img,
			&settings->game->texture[NO_TEXTURE].bits_per_pixel,
			&settings->game->texture[NO_TEXTURE].line_length,
			&settings->game->texture[NO_TEXTURE].endian);
	settings->game->texture[SO_TEXTURE].img
		= mlx_xpm_file_to_image(settings->window->mlx,
			settings->config->so_texture,
			&settings->game->texture[SO_TEXTURE].img_width,
			&settings->game->texture[SO_TEXTURE].img_height);
	settings->game->texture[SO_TEXTURE].addr
		= mlx_get_data_addr(settings->game->texture[SO_TEXTURE].img,
			&settings->game->texture[SO_TEXTURE].bits_per_pixel,
			&settings->game->texture[SO_TEXTURE].line_length,
			&settings->game->texture[SO_TEXTURE].endian);
}

void	load_west_east_texture(t_settings *settings)
{
	settings->game->texture[WE_TEXTURE].img
		= mlx_xpm_file_to_image(settings->window->mlx,
			settings->config->we_texture,
			&settings->game->texture[WE_TEXTURE].img_width,
			&settings->game->texture[WE_TEXTURE].img_height);
	settings->game->texture[WE_TEXTURE].addr
		= mlx_get_data_addr(settings->game->texture[WE_TEXTURE].img,
			&settings->game->texture[WE_TEXTURE].bits_per_pixel,
			&settings->game->texture[WE_TEXTURE].line_length,
			&settings->game->texture[WE_TEXTURE].endian);
	settings->game->texture[EA_TEXTURE].img
		= mlx_xpm_file_to_image(settings->window->mlx,
			settings->config->ea_texture,
			&settings->game->texture[EA_TEXTURE].img_width,
			&settings->game->texture[EA_TEXTURE].img_height);
	settings->game->texture[EA_TEXTURE].addr
		= mlx_get_data_addr(settings->game->texture[EA_TEXTURE].img,
			&settings->game->texture[EA_TEXTURE].bits_per_pixel,
			&settings->game->texture[EA_TEXTURE].line_length,
			&settings->game->texture[EA_TEXTURE].endian);
}

void	load_textures(t_settings *settings)
{
	load_north_south_texture(settings);
	load_west_east_texture(settings);
	load_sprite_texture(settings);
}
