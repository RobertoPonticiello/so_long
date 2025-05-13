#include "so_long.h"

int	check_reachable(char **filled_map, t_map *original)
{
	int	i;
	int	j;

	i = 0;
	while (i < original->height)
	{
		j = 0;
		while (j < original->width)
		{
			if ((original->grid[i][j] == 'C' || original->grid[i][j] == 'E')
				&& filled_map[i][j] != 'F')
				return (error_message("Not all elements are reachable"));
			j++;
		}
		i++;
	}
	return (1);
}

int	check_valid_path(t_map *map)
{
	char	**temp_map;
	int		result;

	temp_map = copy_map(map);
	if (!temp_map)
		return (0);
	flood_fill(temp_map, map->player_x, map->player_y, map);
	result = check_reachable(temp_map, map);
	free_temp_map(temp_map, map->height);
	return (result);
}

int	validate_map(t_map *map, char *filename)
{
	if (!read_map(map, filename))
		return (0);
	if (!check_map_structure(map))
		return (0);
	if (!check_map_elements(map))
		return (0);
	if (!check_valid_path(map))
		return (0);
	return (1);
}
