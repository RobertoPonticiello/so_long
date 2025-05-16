/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:57:16 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/16 19:57:17 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_game_over_message(t_game *game)
{
	char	*message;
	int		x_pos;
	int		y_pos;

	if (game->game_over)
	{
		if (game->collected == game->map.collectibles)
			message = "You Win!";
		else
			message = "Game Over!";
		x_pos = (game->map.width * TILE_SIZE) / 2 - 50;
		y_pos = (game->map.height * TILE_SIZE) / 2;
		mlx_string_put(game->mlx, game->win, x_pos, y_pos, 0x00FF0000, message);
	}
}

static char	*create_counter_string(char *collect_str, char *total_str)
{
	char	*tmp;
	char	*display;

	tmp = ft_strjoin("Collected: ", collect_str);
	if (!tmp)
		return (NULL);
	display = ft_strjoin(tmp, "/");
	free(tmp);
	if (!display)
		return (NULL);
	tmp = display;
	display = ft_strjoin(tmp, total_str);
	free(tmp);
	return (display);
}

static void	display_collectibles_counter(t_game *game)
{
	char	*collect_str;
	char	*total_str;
	char	*display;

	collect_str = ft_itoa(game->collected);
	total_str = ft_itoa(game->map.collectibles);
	display = NULL;
	if (collect_str && total_str)
	{
		display = create_counter_string(collect_str, total_str);
		if (display)
		{
			mlx_string_put(game->mlx, game->win, 10, 40, 0x00FFFFFF, display);
			free(display);
		}
	}
	if (collect_str)
		free(collect_str);
	if (total_str)
		free(total_str);
}

static void	update_enemy_animation(t_game *game)
{
	if (game->frame_counter % 15 == 0)
		game->enemy_frame = (game->enemy_frame + 1) % 2;
}

int	game_loop(t_game *game)
{
	game->frame_counter++;
	animate_player(game);
	move_enemies(game);
	handle_game_over_message(game);
	update_enemy_animation(game);
	render_game(game);
	display_collectibles_counter(game);
	return (0);
}
