#include "so_long.h"

void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_tile(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map.grid[y][x];
	put_image(game, game->img_floor.img, x, y);
	
	if (tile == '1')
		put_image(game, game->img_wall.img, x, y);
	else if (tile == 'C')
		put_image(game, game->img_collect.img, x, y);
	else if (tile == 'E')
		put_image(game, game->img_exit.img, x, y);
	else if (tile == 'P')
		put_image(game, game->img_player[game->player_frame].img, x, y);
}

void	render_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.enemies)
	{
		put_image(game, game->img_floor.img,
			game->enemies[i].x, game->enemies[i].y);
		put_image(game, game->img_enemy[game->enemy_frame].img,
			game->enemies[i].x, game->enemies[i].y);
		i++;
	}
}

void	render_moves(t_game *game)
{
	char	*moves_str;
	char	*display;

	moves_str = ft_itoa(game->moves);
	if (!moves_str)
		return ;
		
	display = ft_strjoin("Moves: ", moves_str);
	free(moves_str);
	
	if (!display)
		return ;
		
	// Disegna un rettangolo nero sopra dove sarà mostrato il testo
	mlx_string_put(game->mlx, game->win, 10, 20, 0x00FFFFFF, display);
	free(display);
}

void	render_game(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
	
	render_enemies(game);
	render_moves(game);
}