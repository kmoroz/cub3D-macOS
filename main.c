/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 17:53:04 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/18 11:14:50 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <stdlib.h>

t_window_settings	set_up_window(t_cub config)
{
	t_window_settings	window;

	window.mlx = mlx_init(); //TODO: malloc check!!!
	window.window = mlx_new_window(window.mlx,
		config.x_res, config.y_res, "cub3D");
	window.img = mlx_new_image(window.mlx,
			config.x_res, config.y_res);
	return (window);
}

void	count_sprites(t_settings *settings)
{
	int		x;
	int		y;
	t_list	*temp;

	temp = settings->config->map;
	settings->game->sprite->num = 0;
	x = 0;
	y = 0;
	while (temp)
	{
		while ((temp->row[x]))
		{
			if (temp->row[x] == '2')
				settings->game->sprite->num++;
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void init_sprite_position_distance(t_settings *settings, t_sprite *sprite)
{
	int		x;
	int		y;
	int		count;
	t_list	*temp;

	temp = settings->config->map;
	x = 0;
	y = 0;
	count = 0;
	while (temp)
	{
		while ((temp->row[x]))
		{
			if (temp->row[x] == '2')
			{
				sprite->x[count] = x * TILE_SIZE + TILE_SIZE / 2;
				sprite->y[count] = y * TILE_SIZE + TILE_SIZE / 2;
				sprite->distance[count] = 0;
				sprite->visible[count] = 0;
				count++;
			}
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	init_sprite(t_settings *settings)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	sprite->x = malloc(sizeof(float) * sprite->num);
	sprite->y = malloc(sizeof(float) * sprite->num);
	sprite->distance = malloc(sizeof(float) * sprite->num);
	sprite->visible = malloc(sizeof(int) * sprite->num);
	sprite->angle = malloc(sizeof(float) * sprite->num);
	sprite->top = malloc(sizeof(float) * sprite->num);
	sprite->bottom = malloc(sizeof(float) * sprite->num);
	sprite->screen_pos_x = malloc(sizeof(float) * sprite->num);
	sprite->right_x = malloc(sizeof(float) * sprite->num);
	sprite->left_x = malloc(sizeof(float) * sprite->num);
	init_sprite_position_distance(settings, sprite);
	settings->game->sprite = sprite;
	count_sprites(settings);
}

void	init_ray(t_settings *settings)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->ray_angle = 0;
	ray->vertical_wall_hit_x = 0;
	ray->vertical_wall_hit_y = 0;
	ray->horizontal_wall_hit_x = 0;
	ray->horizontal_wall_hit_y = 0;
	ray->was_hit_vertical = 0;
	ray->distance = malloc(sizeof(float) * settings->config->x_res);
	settings->ray = ray;
}

void	init_player_position(t_settings *settings)
{
	float	x;
	float	y;
	int		count;
	t_list	*temp;

	temp = settings->config->map;
	x = 0;
	y = 0;
	while (temp)
	{
		count = 0;
		while ((temp->row[count]))
		{
			if (ft_strchr("NSEW", temp->row[count]))
			{
				settings->game->player->xpos = x * TILE_SIZE + TILE_SIZE / 2;
				settings->game->player->ypos = y * TILE_SIZE + TILE_SIZE / 2;
			}
			x++;
			count++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	init_player_angle(t_settings *settings)
{
	int		x;
	int		y;
	t_list	*temp;

	temp = settings->config->map;
	x = 0;
	y = 0;
	while (temp)
	{
		while ((temp->row[x]))
		{
			if (temp->row[x] == 'N')
				settings->game->player->angle = PI * 1.5;
			else if (temp->row[x] == 'W')
				settings->game->player->angle = PI;
			else if (temp->row[x] == 'E')
				settings->game->player->angle = 0;
			else if (temp->row[x] == 'S')
				settings->game->player->angle = PI * 0.5;
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}

void	init_player(t_settings *settings)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->walk_speed = 4;
	player->turn_speed = 20 * (PI / 180);
	settings->game->player = player;
	init_player_position(settings);
	init_player_angle(settings);
}

int	x_button_hook(t_window_settings *window)
{
	printf("\n\U0000274C Red cross pressed. Game terminated. \U0000274C");
	exit(0);
	return (0);
}

void	set_up_game(t_window_settings *window, t_game_state *game, t_cub *config)
{
	t_settings *settings;
	t_wall *wall;
	int *colour_buffer;

	settings = malloc(sizeof(t_settings));
	wall = malloc(sizeof(t_wall));
	settings->window = malloc(sizeof(t_window_settings));
	settings->game = malloc(sizeof(t_game_state));
	settings->config = malloc(sizeof(t_cub));
	settings->ray = malloc(sizeof(t_ray));
	settings->game = game;
	settings->game->wall = wall;
	settings->game->wall->wall_top_pixel = 0;
	settings->game->wall->wall_strip_height = 0;
	settings->game->wall->wall_height = 0;
	settings->game->wall->wall_bottom_pixel = 0;
	settings->game->wall->proj_plane_distance = 0;
	settings->window = window;
	settings->config = config;
	init_player(settings);
	init_ray(settings);
	load_textures(settings);
	init_sprite(settings);
	mlx_hook(window->window, 17, 1L << 17, &x_button_hook, settings->window);
	mlx_hook(window->window, 2, 1L << 0, key_press_handler, settings);
	mlx_hook(window->window, 3, 0, key_release_handler, settings);
	mlx_loop_hook(window->mlx, refresh, settings);
}

int	main(int argc, char **argv)
{
	t_cub				config;
	t_game_state		game;
	t_window_settings	window;

	//ft_memset(&game, 0, sizeof(game)); //TO DO: is it necessary?
	//parse
	if (check_args(argc, argv) == ERROR)
		return (ERROR);
	config = parse_file(argv[1]);
	if (check_config_file(config) == ERROR)
		return (ERROR);
	//set up mlx
	window = set_up_window(config);
	//set up game
	set_up_game(&window, &game, &config);
	//loop
	mlx_loop(window.mlx);
}
