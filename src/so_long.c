/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:20:56 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/13 19:27:49 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./so_long map_file.ber\n", 2);
		return (1);
	}
	if (!init_game(&game, argv[1]))
	{
		ft_putstr_fd("Error\nFailed to initialize the game\n", 2);
		return (1);
	}
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
