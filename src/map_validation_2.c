#include "so_long.h"

int	process_character(t_map *map, char c, int i, int j)
{
	if (c == 'P')
	{
		map->player_x = j;
		map->player_y = i;
		return (1);
	}
	else if (c == 'E')
	{
		map->exit_x = j;
		map->exit_y = i;
		return (1);
	}
	else if (c == 'C')
		return (1);
	else if (c == 'N')
	{
		map->enemies++;
		return (1);
	}
	else if (c == '0' || c == '1')
		return (0);
	else
		return (-1);
}

static int	traverse_map(t_map *map, int *player_count, int *exit_count,
		int *collectible_count)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			c = map->grid[i][j];
			if (c == 'P')
				(*player_count)++;
			else if (c == 'E')
				(*exit_count)++;
			else if (c == 'C')
				(*collectible_count)++;
			if (process_character(map, c, i, j) < 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

// Controlla che ci sia esattamente 1 player, 1 exit e ≥1 collectible
static int	validate_counts(int p, int e, int c)
{
	if (p != 1 || e != 1 || c < 1)
		return (error_message("Invalid number of elements"));
	return (1);
}

int	check_map_elements(t_map *map)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	if (traverse_map(map, &player_count, &exit_count, &collectible_count) < 0)
		return (error_message("Invalid character in map"));
	map->collectibles = collectible_count;
	return (validate_counts(player_count, exit_count, collectible_count));
}

char	**copy_map(t_map *map)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		temp[i] = ft_strdup(map->grid[i]);
		if (!temp[i])
		{
			free_temp_map(temp, i);
			return (NULL);
		}
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
