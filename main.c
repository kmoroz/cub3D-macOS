/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 17:53:04 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/07/21 15:12:39 by ksmorozo      ########   odam.nl         */
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
	check_resolution(config);
	window.window = mlx_new_window(window.mlx,
			config->x_res, config->y_res, "cub3D");
	window.img = mlx_new_image(window.mlx,
			config->x_res, config->y_res);
	window.addr = (int *)mlx_get_data_addr(window.img,
			&window.bits_per_pixel, &window.line_length,
			&window.endian);
	return (window);
}

void	set_up_game(t_window_settings *window,
	t_game_state *game, t_cub *config)
{
	t_settings	*settings;

	settings = malloc(sizeof(t_settings));
	if (!settings)
		ft_error(MALLOC);
	settings->game = game;
	settings->window = window;
	init_config(settings, config);
	init_wall(settings);
	init_player(settings);
	init_ray(settings);
	load_textures(settings);
	init_sprite(settings);
	mlx_hook(window->window, 17, 1L << 17, &x_button_hook, settings);
	mlx_hook(window->window, 2, 1L << 0, key_press_handler, settings);
	mlx_hook(window->window, 3, 0, key_release_handler, settings);
	mlx_loop_hook(window->mlx, refresh, settings);
}

int	main(int argc, char **argv)
{
	t_cub				config;
	t_game_state		game;
	t_window_settings	window;

	check_args(argc, argv);
	init_texture_path(&config);
	parse_file(argv[1], &config);
	check_config_file(config);
	window = set_up_window(&config);
	set_up_game(&window, &game, &config);
	mlx_loop(window.mlx);
}
