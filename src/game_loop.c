/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:55:33 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/16 19:55:34 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_map(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

// Libera tutte le immagini caricate da MLX
static void	free_images(t_game *game)
{
	int	i;

	if (!game || !game->mlx)
		return ;
	mlx_destroy_image(game->mlx, game->img_wall.img);
	mlx_destroy_image(game->mlx, game->img_floor.img);
	mlx_destroy_image(game->mlx, game->img_collect.img);
	mlx_destroy_image(game->mlx, game->img_exit.img);
	i = 0;
	while (i < 4)
		mlx_destroy_image(game->mlx, game->img_player[i++].img);
	i = 0;
	while (i < 2)
		mlx_destroy_image(game->mlx, game->img_enemy[i++].img);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	free_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(game->map.grid, game->map.height);
	if (game->enemies)
		free(game->enemies);
}

int	close_window(t_game *game)
{
	if (!game)
		exit(0);
	cleanup_game(game);
	exit(0);
	return (0);
}

void	animate_player(t_game *game)
{
	if (game->frame_counter % 10 == 0)
		game->player_frame = (game->player_frame + 1) % 4;
}
