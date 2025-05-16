/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:57:07 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/16 19:57:08 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
