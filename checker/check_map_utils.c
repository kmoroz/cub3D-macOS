#include "../cub3d.h"

void	check_player(t_cub config)
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
				ft_error(PLAYER_INVALID);
			else if (ft_strchr("NSEW", config.map->row[x]))
				count++;
			x++;
		}
		config.map = config.map->next;
		y++;
		x = 0;
	}
	if (count != 1)
		ft_error(PLAYER_INVALID);
}

void	check_allowed_chars(t_cub config)
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
				ft_error(MAP_INVALID);
		}
		config.map = config.map->next;
		y++;
		x = 0;
	}
}

int	is_map_on_top(t_cub config)
{
	if (config.type_identifier_num < TYPE_IDENTIFIERS)
		return (1);
	else
		return (0);
}

void	contains_sprites(t_cub *config)
{
	int		x;
	int		y;
	t_list	*temp;

	x = 0;
	y = 0;
	temp = config->map;
	while (temp)
	{
		while ((temp->row[x]))
		{
			if (ft_strchr("2", temp->row[x]))
			{
				config->contains_sprites = 1;
				break ;
			}
			x++;
		}
		temp = temp->next;
		y++;
		x = 0;
	}
}
