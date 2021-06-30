#include "../cub3d.h"
#include <stdio.h>

void	check_max_rgb_value(t_cub config)
{
	int	count;

	count = 0;
	while (count < 3)
	{
		if (config.floor_colour[count] > 255
			|| config.ceiling_colour[count] > 255)
			ft_error(RGB_EXCEEDED);
		count++;
	}
}

int	veirify_rgb_input(char c)
{
	if (c == '-')
		return (ERROR);
	if (ft_isalpha(c))
		return (ERROR);
	return (OK);
}

void	is_rgb_present(t_cub config)
{
	int	count;

	count = 0;
	while (count < 3)
	{
		if (config.floor_colour[count] == ERROR
			|| config.ceiling_colour[count] == ERROR)
			ft_error(RGB_INVALID);
		count++;
	}
}
