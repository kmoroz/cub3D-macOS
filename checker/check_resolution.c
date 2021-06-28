#include "../cub3d.h"
#include "../mlx/mlx.h"

void	verify_max_screen_size(t_window_settings window, t_cub *config)
{
	int	current_x_res;
	int	current_y_res;

	mlx_get_screen_size(window.mlx, &current_x_res, &current_y_res);
	if (config->x_res > current_x_res)
		config->x_res = current_x_res;
	if (config->y_res > current_y_res)
		config->y_res = current_y_res;
}

int	veirify_resolution_input(char c)
{
	if (c == '-')
		return (ERROR);
	if (ft_isalpha(c))
		return (ERROR);
	return (OK);
}
