/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 11:49:57 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/15 16:12:01 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"

void	load_textures(t_settings *settings)
{
	int	bpp;
	int	size_line;
	int	endian;

	settings->game->texture[NO_TEXTURE].img = mlx_xpm_file_to_image(settings->window->mlx,
		settings->config->no_texture, &settings->game->texture[NO_TEXTURE].img_width,
		&settings->game->texture[NO_TEXTURE].img_height);
	settings->game->texture[NO_TEXTURE].colour_buffer = (int *)mlx_get_data_addr(settings->game->texture[NO_TEXTURE].img,
		&bpp, &size_line, &endian);

	settings->game->texture[SO_TEXTURE].img = mlx_xpm_file_to_image(settings->window->mlx,
		settings->config->so_texture, &settings->game->texture[SO_TEXTURE].img_width,
		&settings->game->texture[SO_TEXTURE].img_height);
	settings->game->texture[SO_TEXTURE].colour_buffer = (int *)mlx_get_data_addr(settings->game->texture[SO_TEXTURE].img,
		&bpp, &size_line, &endian);

	settings->game->texture[WE_TEXTURE].img = mlx_xpm_file_to_image(settings->window->mlx,
		settings->config->we_texture, &settings->game->texture[WE_TEXTURE].img_width,
		&settings->game->texture[WE_TEXTURE].img_height);
	settings->game->texture[WE_TEXTURE].colour_buffer = (int *)mlx_get_data_addr(settings->game->texture[WE_TEXTURE].img,
		&bpp, &size_line, &endian);

	settings->game->texture[EA_TEXTURE].img = mlx_xpm_file_to_image(settings->window->mlx,
		settings->config->ea_texture, &settings->game->texture[EA_TEXTURE].img_width,
		&settings->game->texture[EA_TEXTURE].img_height);
	settings->game->texture[EA_TEXTURE].colour_buffer = (int *)mlx_get_data_addr(settings->game->texture[EA_TEXTURE].img,
		&bpp, &size_line, &endian);

	settings->game->texture[SPRITE_TEXTURE].img = mlx_xpm_file_to_image(settings->window->mlx,
		settings->config->sp_texture, &settings->game->texture[SPRITE_TEXTURE].img_width,
		&settings->game->texture[SPRITE_TEXTURE].img_height);
	settings->game->texture[SPRITE_TEXTURE].colour_buffer = (int *)mlx_get_data_addr(settings->game->texture[SPRITE_TEXTURE].img,
				&bpp, &size_line, &endian);

	settings->game->texture[ANIMATION_TEX].img = mlx_xpm_file_to_image(settings->window->mlx,
		"./textures/animation.xpm", &settings->game->texture[ANIMATION_TEX].img_width,
		&settings->game->texture[ANIMATION_TEX].img_height);
	settings->game->texture[ANIMATION_TEX].colour_buffer = (int *)mlx_get_data_addr(settings->game->texture[ANIMATION_TEX].img,
				&bpp, &size_line, &endian);
}
