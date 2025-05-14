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

int	load_image(t_game *game, t_img *img, char *path)
{
	if (!game || !img || !path)
		return (0);
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
	{
		ft_putstr_fd("Error\nFailed to load image: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

void	init_images(t_game *game)
{
	load_image(game, &game->img_wall, "textures/wall.xpm");
	load_image(game, &game->img_floor, "textures/floor.xpm");
	load_image(game, &game->img_collect, "textures/collectible.xpm");
	load_image(game, &game->img_exit, "textures/exit.xpm");
	load_image(game, &game->img_player[0], "textures/player1.xpm");
	load_image(game, &game->img_player[1], "textures/player2.xpm");
	load_image(game, &game->img_player[2], "textures/player3.xpm");
	load_image(game, &game->img_player[3], "textures/player4.xpm");
	load_image(game, &game->img_enemy[0], "textures/enemy1.xpm");
	load_image(game, &game->img_enemy[1], "textures/enemy2.xpm");
}
