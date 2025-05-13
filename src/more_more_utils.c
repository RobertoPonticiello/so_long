#include "so_long.h"

static int	handle_enemy_collision(t_game *game, int new_x, int new_y)
{
	if (check_enemy_collision(game, new_x, new_y))
	{
		game->game_over = 1;
		ft_putstr_fd("Game Over! You hit an enemy.\n", 1);
		return (1);
	}
	return (0);
}

static void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->map.grid[new_y][new_x] = '0';
		game->collected++;
	}
}

static int	handle_exit(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'E')
	{
		if (game->collected == game->map.collectibles)
		{
			game->game_over = 1;
			ft_putstr_fd("You win!\n", 1);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	game->map.grid[new_y][new_x] = 'P';
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	game->moves++;
	printf("Moves: %d\n", game->moves);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (!is_valid_position(game, new_x, new_y))
		return ;

	if (handle_enemy_collision(game, new_x, new_y))
		return ;

	handle_collectible(game, new_x, new_y);

	if (!handle_exit(game, new_x, new_y))
		return ;

	update_player_position(game, new_x, new_y);
}