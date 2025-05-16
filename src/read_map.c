/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:56:49 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/16 19:56:50 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	process_line(char *line, size_t *line_len, t_map *map)
{
	*line_len = ft_strlen(line);
	if (*line_len > 0 && line[*line_len - 1] == '\n')
	{
		line[*line_len - 1] = '\0';
		(*line_len)--;
	}
	if (map->width == 0)
		map->width = *line_len;
	return (1);
}

/**
 * Alloca un nuovo buffer per la griglia con una riga aggiuntiva
 */
static char	**allocate_new_grid(t_map *map, char *line)
{
	char	**temp;

	temp = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	return (temp);
}

/**
 * Copia le righe esistenti nel nuovo buffer
 */
static int	copy_existing_rows(t_map *map, char **temp, char *line)
{
	int	i;

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
	return (1);
}

/**
 * Aggiorna la griglia della mappa con la nuova riga
 */
static void	update_map_grid(t_map *map, char **temp, char *line)
{
	free(line);
	if (map->grid)
		free(map->grid);
	map->grid = temp;
	map->height++;
}

/**
 * Legge una linea dal file e la aggiunge alla mappa
 */
int	read_map_line(t_map *map, int fd)
{
	char	*line;
	char	**temp;
	size_t	line_len;

	line = get_next_line(fd);
	if (!line)
		return (0);
	if (!process_line(line, &line_len, map))
		return (0);
	temp = allocate_new_grid(map, line);
	if (!temp)
		return (0);
	if (!copy_existing_rows(map, temp, line))
		return (0);
	update_map_grid(map, temp, line);
	return (1);
}
