#include "../cub3d.h"
#include <stdlib.h>
#include "../mlx/mlx.h"

void	free_sprite(t_sprite *sprite)
{
	free(sprite->bottom);
	free(sprite->top);
	free(sprite->visible);
	free(sprite->x);
	free(sprite->y);
	free(sprite->distance);
	free(sprite->angle);
	free(sprite->screen_pos_x);
	free(sprite->left_x);
	free(sprite->right_x);
	free(sprite);
}

void	free_texture(t_settings *settings, t_texture *texture)
{
	int	count;

	count = 0;
	free(settings->config->ea_texture);
	free(settings->config->no_texture);
	free(settings->config->so_texture);
	free(settings->config->we_texture);
	if (settings->config->contains_sprites)
	{
		free(settings->config->sp_texture);
		mlx_destroy_image(settings->window->mlx, texture[SPRITE_TEXTURE].img);
		mlx_destroy_image(settings->window->mlx, texture[ANIMATION_TEX].img);
	}
	while (count < NUM_TEXTURES - 2)
	{
		mlx_destroy_image(settings->window->mlx, texture[count].img);
		count++;
	}
}

void	free_map(t_settings *settings)
{
	t_list	*head;

	while (settings->config->map)
	{
		head = settings->config->map->next;
		free(settings->config->map->row);
		free(settings->config->map);
		settings->config->map = head;
	}
	settings->config->map = NULL;
}

void	free_ray(t_ray *ray)
{
	free(ray->distance);
	free(ray);
}

int	free_everything(t_settings *settings)
{
	if (settings->window->mlx)
	{
		mlx_clear_window(settings->window->mlx, settings->window->window);
		mlx_destroy_image(settings->window->mlx, settings->window->img);
		mlx_destroy_window(settings->window->mlx, settings->window->window);
	}
	free_sprite(settings->game->sprite);
	free_texture(settings, settings->game->texture);
	free_map(settings);
	free_ray(settings->ray);
	free(settings->game->player);
	free(settings->game->wall);
	free(settings->window->mlx);
	free(settings);
	return (0);
}
