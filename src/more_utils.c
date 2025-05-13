/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:48 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/13 19:14:28 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (game->game_over)
		return (0);
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, game->map.player_x, game->map.player_y - 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, game->map.player_x, game->map.player_y + 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, game->map.player_x - 1, game->map.player_y);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, game->map.player_x + 1, game->map.player_y);
	return (0);
}

int	is_valid_position(t_game *game, int new_x, int new_y)
{
	if (game->game_over)
		return (0);
	if (new_x < 0 || new_y < 0 || new_x >= game->map.width
		|| new_y >= game->map.height)
		return (0);
	if (game->map.grid[new_y][new_x] == '1')
		return (0);
	return (1);
}
