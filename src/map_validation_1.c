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

int	read_map_line(t_map *map, int fd)
{
	char	*line;
	char	**temp;
	int		i;
	size_t	line_len;

	line = get_next_line(fd);
	if (!line)
		return (0);
	
	line_len = ft_strlen(line);
	
	// Se la riga termina con newline, rimuovilo
	if (line_len > 0 && line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
		line_len--;
	}
	
	// Se è la prima riga, salviamo la larghezza
	if (map->width == 0)
		map->width = line_len;
	
	temp = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!temp)
	{
		free(line);
		return (0);
	}
	
	i = 0;
	while (i < map->height)
	{
		temp[i] = map->grid[i];
		i++;
	}
	
	temp[i] = ft_strdup(line);
	if (!temp[i])
	{
		free(line);
		free(temp);
		return (0);
	}
	
	temp[i + 1] = NULL;
	free(line);
	
	if (map->grid)
		free(map->grid);
	
	map->grid = temp;
	map->height++;
	return (1);
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
			if ((i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
				&& map->grid[i][j] != '1')
				return (error_message("Map is not surrounded by walls"));
			j++;
		}
		i++;
	}
	return (1);
}