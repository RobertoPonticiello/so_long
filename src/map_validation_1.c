#include "so_long.h"

int	error_message(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	check_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	return (ft_strncmp(dot, ".ber", 10) == 0);
}

int	read_map(t_map *map, char *filename)
{
	int	fd;

	if (!check_extension(filename))
		return (error_message("Invalid file extension. Must be .ber"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_message("Cannot open file"));
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->enemies = 0;
	while (read_map_line(map, fd))
		;
	close(fd);
	if (map->height < 3)
		return (error_message("Map too small"));
	return (1);
}

int	check_map_structure(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		if ((int)ft_strlen(map->grid[i]) != map->width)
			return (error_message("Map is not rectangular"));
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if ((i == 0 || i == map->height - 1 || j == 0 || j == map->width
					- 1) && map->grid[i][j] != '1')
				return (error_message("Map is not surrounded by walls"));
			j++;
		}
		i++;
	}
	return (1);
}
