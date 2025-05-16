/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:55:39 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/16 19:55:40 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_enemy_collision(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->map.enemies)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

int	check_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (1);
	return (game->map.grid[y][x] == '1');
}

void	move_enemy(t_game *game, int idx)
{
	int	new_x;
	int	new_y;

	new_x = game->enemies[idx].x + game->enemies[idx].dir_x;
	new_y = game->enemies[idx].y + game->enemies[idx].dir_y;
	if (check_wall(game, new_x, new_y))
	{
		game->enemies[idx].dir_x *= -1;
		game->enemies[idx].dir_y *= -1;
		return ;
	}
	game->enemies[idx].x = new_x;
	game->enemies[idx].y = new_y;
	if (new_x == game->map.player_x && new_y == game->map.player_y)
	{
		game->game_over = 1;
		ft_putstr_fd("Game Over! An enemy got you.\n", 1);
	}
}

void	move_enemies(t_game *game)
{
	int	i;

	if (game->frame_counter % ENEMY_MOVE_INTERVAL != 0)
		return ;
	i = 0;
	while (i < game->map.enemies)
	{
		move_enemy(game, i);
		i++;
	}
	game->enemy_frame = (game->enemy_frame + 1) % 2;
}
