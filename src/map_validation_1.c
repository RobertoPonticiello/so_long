#include "so_long.h"

int	error_message(char *msg)
{
	ft_putstr_fd("SBAGLIATO!! ", 2);
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

int	read_map_line(t_map *map, int fd)
{
	char	*line;
	char	**temp;
	int		i;

	line = get_next_line(fd);
	if (!line)
		return (0);
	if (map->width == 0)
		map->width = ft_strlen(line) - 1;
	temp = (char **)malloc(sizeof(char *) * (map->height + 2)); //MA DIO CANE MALEDETTO 
	if (!temp)
		return (0);
	i = 0;
	while (i < map->height)
	{
		temp[i] = map->grid[i];
		i++;
	}
	line[ft_strlen(line) - 1] = '\0';
	temp[i] = ft_strdup(line);
	temp[i + 1] = NULL;
	free(line);
	free(map->grid);
	map->grid = temp;
	map->height++;
	return (1);
}