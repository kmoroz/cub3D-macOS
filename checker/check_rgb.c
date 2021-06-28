#include "../cub3d.h"
#include <stdio.h>

int	check_max_rgb_value(t_cub config)
{
	int	count;

	count = 0;
	while (count < 3)
	{
		if (config.floor_colour[count] > 255
			|| config.ceiling_colour[count] > 255)
		{
			printf("Error\n\U0001f4a9 Max RGB value exceeded \U0001f4a9\n");
			return (ERROR);
		}
		count++;
	}
	return (OK);
}

int	veirify_rgb_input(char c)
{
	if (c == '-')
		return (ERROR);
	if (ft_isalpha(c))
		return (ERROR);
	return (OK);
}

int	is_rgb_present(t_cub config)
{
	int	count;

	count = 0;
	while (count < 3)
	{
		if (config.floor_colour[count] == ERROR
			|| config.ceiling_colour[count] == ERROR)
		{
			printf("Error\n\U0001f4a9 RGB value missing \U0001f4a9\n");
			return (ERROR);
		}
		count++;
	}
	return (OK);
}
