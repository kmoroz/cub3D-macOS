#include "../cub3d.h"

int	check_player(t_cub config)
{
	int		x;
	int		y;
	int		count;

	x = 0;
	y = 0;
	count = 0;
	while (config.map)
	{
		while ((config.map->row[x]))
		{
			if (ft_isalpha(config.map->row[x])
				&& !ft_strchr("NSEW", config.map->row[x]))
				return (ERROR);
			else if (ft_strchr("NSEW", config.map->row[x]))
				count++;
			x++;
		}
		config.map = config.map->next;
		y++;
		x = 0;
	}
	if (count == 1)
		return (OK);
	return (ERROR);
}

int	check_allowed_chars(t_cub config)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (config.map)
	{
		while ((config.map->row[x]))
		{
			if (ft_strchr("NSEW201", config.map->row[x])
				|| ft_isspace(config.map->row[x]))
				x++;
			else
				return (ERROR);
		}
		config.map = config.map->next;
		y++;
		x = 0;
	}
	return (OK);
}

int	is_map_on_top(t_cub config)
{
	if (config.type_identifier_num < 8)
		return (1);
	else
		return (0);
}
