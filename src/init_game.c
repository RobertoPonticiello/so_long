#include "so_long.h"

int	init_mlx_environment(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "so_long");
	if (!game->win)
		return (0);
	return (1);
}

void	init_image_pointers(t_game *game)
{
	int	i;

	game->img_wall.img = NULL;
	game->img_floor.img = NULL;
	game->img_collect.img = NULL;
	game->img_exit.img = NULL;
	i = 0;
	while (i < 4)
	{
		game->img_player[i].img = NULL;
		i++;
	}
	i = 0;
	while (i < 2)
	{
		game->img_enemy[i].img = NULL;
		i++;
	}
}

int	validate_loaded_images(t_game *game)
{
	if (!game->img_wall.img || !game->img_floor.img || !game->img_collect.img
		|| !game->img_exit.img)
	{
		ft_putstr_fd("Error\nFailed to load game textures\n", 2);
		return (0);
	}
	return (1);
}

void	init_game_state(t_game *game)
{
	game->collected = 0;
	game->moves = 0;
	game->game_over = 0;
	game->player_frame = 0;
	game->enemy_frame = 0;
	game->frame_counter = 0;
}

int	init_game(t_game *game, char *map_file)
{
	ft_memset(game, 0, sizeof(t_game));
	if (!validate_map(&game->map, map_file))
		return (0);
	if (!init_mlx_environment(game))
		return (0);
	init_image_pointers(game);
	init_images(game);
	if (!validate_loaded_images(game))
		return (0);
	if (!init_enemies(game))
		return (0);
	init_game_state(game);
	return (1);
}
