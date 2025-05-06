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

int	check_map_elements(t_map *map)
{
	int	i;
	int	j;
	int	player_count;
	int	exit_count;
	int	collectible_count;

	i = 0;
	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'P')
				player_count++;
			else if (map->grid[i][j] == 'E')
				exit_count++;
			else if (map->grid[i][j] == 'C')
				collectible_count++;
			if (process_character(map, map->grid[i][j], i, j) < 0)
				return (error_message("Invalid character in map"));
			j++;
		}
		i++;
	}
	map->collectibles = collectible_count;
	if (player_count != 1 || exit_count != 1 || collectible_count < 1)
		return (error_message("Invalid number of elements"));
	return (1);
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

void	free_temp_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	flood_fill(char **map, int x, int y, t_map *original)
{
	if (x < 0 || y < 0 || x >= original->width || y >= original->height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, original);
	flood_fill(map, x - 1, y, original);
	flood_fill(map, x, y + 1, original);
	flood_fill(map, x, y - 1, original);
}
