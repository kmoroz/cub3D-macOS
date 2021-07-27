/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 18:47:56 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/07/27 14:46:03 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int	x_button_hook(t_settings *settings)
{
	printf("\n\U0000274C Red cross pressed. Game terminated. \U0000274C\n");
	exit(free_everything(settings));
	return (0);
}

int	key_press_handler(int keycode, t_settings *settings)
{
	if (keycode == KEY_ESC)
	{
		printf("\n\U00002B1B Esc pressed. Thanks for playing! \U00002B1B\n");
		exit(free_everything(settings));
	}
	else if (keycode == KEY_A)
		settings->game->player->sidewalk = 1;
	else if (keycode == KEY_D)
		settings->game->player->sidewalk = 1;
	else if (keycode == KEY_LEFT)
		settings->game->player->turn_direction = -1;
	else if (keycode == KEY_RIGHT)
		settings->game->player->turn_direction = 1;
	if (keycode == KEY_W || keycode == KEY_D)
		settings->game->player->walk_direction = 1;
	if (keycode == KEY_S || keycode == KEY_A)
		settings->game->player->walk_direction = -1;
	update_player_position(settings, settings->game->player);
	return (0);
}

int	key_release_handler(int keycode, t_settings *settings)
{
	if (keycode == KEY_A)
		settings->game->player->sidewalk = 0;
	else if (keycode == KEY_D)
		settings->game->player->sidewalk = 0;
	else if (keycode == KEY_LEFT)
		settings->game->player->turn_direction = 0;
	else if (keycode == KEY_RIGHT)
		settings->game->player->turn_direction = 0;
	if (keycode == KEY_W || keycode == KEY_D)
		settings->game->player->walk_direction = 0;
	if (keycode == KEY_S || keycode == KEY_A)
		settings->game->player->walk_direction = 0;
	return (0);
}
