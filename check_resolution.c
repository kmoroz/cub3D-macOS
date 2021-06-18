#include "cub3d.h"
#include "mlx/mlx.h"

void	verify_max_screen_size(t_settings *settings)
{
	int	current_x_res;
	int	current_y_res;

	mlx_get_screen_size(settings->window->mlx, &current_x_res, &current_y_res);
	if (settings->config->x_res > current_x_res)
		settings->config->x_res = current_x_res;
	if (settings->config->y_res > current_y_res)
		settings->config->y_res = current_y_res;
}
