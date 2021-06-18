#include "cub3d.h"

int	check_max_rgb_value(t_cub config)
{
	int	count;

	count = 0;
	while (count < 3)
	{
		if (config.floor_colour[count] > 255 || config.floor_colour[count] < 0
			|| config.ceiling_colour[count] > 255
			|| config.ceiling_colour[count] < 0)
			return (ERROR);
		count++;
	}
	return (OK);
}

int veirify_rgb_input(char c)
{
	if (c == '-')
		return (ERROR);
	if (ft_isalpha(c))
		return (ERROR);
	return (OK);
}
