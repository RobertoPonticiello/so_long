#include "so_long.h"

int	load_image(t_game *game, t_img *img, char *path)
{
	// Verifica che i parametri siano validi
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
	// Carica le diverse animazioni per il giocatore
	load_image(game, &game->img_player[0], "textures/player1.xpm");
	load_image(game, &game->img_player[1], "textures/player2.xpm");
	load_image(game, &game->img_player[2], "textures/player3.xpm");
	load_image(game, &game->img_player[3], "textures/player4.xpm");
	// Carica le animazioni per i nemici
	load_image(game, &game->img_enemy[0], "textures/enemy1.xpm");
	load_image(game, &game->img_enemy[1], "textures/enemy2.xpm");
}

void	count_enemies(t_game *game)
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
				count++;
			j++;
		}
		i++;
	}
	game->map.enemies = count;
}

int	init_enemies(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count_enemies(game);
	game->enemies = (t_enemy *)malloc(sizeof(t_enemy) * game->map.enemies);
	if (!game->enemies)
		return (0);
	count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'N')
			{
				game->enemies[count].x = j;
				game->enemies[count].y = i;
				game->enemies[count].dir_x = 1;
				game->enemies[count].dir_y = 0;
				count++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	init_game(t_game *game, char *map_file)
{
	// Inizializza tutti i campi a 0/NULL
	ft_memset(game, 0, sizeof(t_game));

	// Valida la mappa
	if (!validate_map(&game->map, map_file))
		return (0);

	// Inizializza MLX
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);

	// Crea la finestra
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "so_long");
	if (!game->win)
		return (0);

	// Inizializza le immagini
	game->img_wall.img = NULL;
	game->img_floor.img = NULL;
	game->img_collect.img = NULL;
	game->img_exit.img = NULL;

	int i;
	for (i = 0; i < 4; i++)
		game->img_player[i].img = NULL;

	for (i = 0; i < 2; i++)
		game->img_enemy[i].img = NULL;

	// Carica le immagini
	init_images(game);

	// Verifica che tutte le immagini necessarie siano state caricate
	if (!game->img_wall.img || !game->img_floor.img || !game->img_collect.img
		|| !game->img_exit.img)
	{
		ft_putstr_fd("Error\nFailed to load game textures\n", 2);
		return (0);
	}

	// Inizializza i nemici
	if (!init_enemies(game))
		return (0);

	// Inizializza le variabili di gioco
	game->collected = 0;
	game->moves = 0;
	game->game_over = 0;
	game->player_frame = 0;
	game->enemy_frame = 0;
	game->frame_counter = 0;

	return (1);
}