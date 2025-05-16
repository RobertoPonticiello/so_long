/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:57:00 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/16 19:57:01 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_enemies(t_game *game)
{
	int	i;
	int	j;

	game->map.enemies = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'N')
				game->map.enemies++;
			j++;
		}
		i++;
	}
}

void	init_single_enemy(t_game *game, int count, int i, int j)
{
	game->enemies[count].x = j;
	game->enemies[count].y = i;
	game->enemies[count].dir_x = 1;
	game->enemies[count].dir_y = 0;
}

int	find_and_setup_enemies(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'N')
			{
				init_single_enemy(game, count, i, j);
				count++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	init_enemies(t_game *game)
{
	count_enemies(game);
	game->enemies = (t_enemy *)malloc(sizeof(t_enemy) * game->map.enemies);
	if (!game->enemies)
		return (0);
	return (find_and_setup_enemies(game));
}
