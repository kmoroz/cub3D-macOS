/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 17:53:04 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/29 14:59:17 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <stdlib.h>

t_window_settings	set_up_window(t_cub *config)
{
	t_window_settings	window;

	window.mlx = mlx_init();
	verify_max_screen_size(window, config);
	window.window = mlx_new_window(window.mlx,
			config->x_res, config->y_res, "cub3D");
	return (window);
}

void	set_up_game(t_window_settings *window,
	t_game_state *game, t_cub *config)
{
	t_settings	*settings;

	settings = malloc(sizeof(t_settings));
	if (!settings)
		ft_error(MALLOC);
	settings->window = malloc(sizeof(t_window_settings));
	settings->game = malloc(sizeof(t_game_state));
	if (!settings->window || !settings->game)
		ft_error(MALLOC);
	settings->game = game;
	settings->window = window;
	init_config(settings, config);
	init_wall(settings);
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

	if (check_args(argc, argv) == ERROR)
		return (ERROR);
	init_texture_path(&config);
	if (parse_file(argv[1], &config) == ERROR)
		return (ERROR);
	if (check_config_file(config) == ERROR)
		return (ERROR);
	window = set_up_window(&config);
	set_up_game(&window, &game, &config);
	mlx_loop(window.mlx);
}
