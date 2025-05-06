#include "so_long.h"

int	close_window(t_game *game)
{
	int	i;

	if (!game)
		exit(0);
		
	// Libera le immagini
	if (game->img_wall.img)
		mlx_destroy_image(game->mlx, game->img_wall.img);
	if (game->img_floor.img)
		mlx_destroy_image(game->mlx, game->img_floor.img);
	if (game->img_collect.img)
		mlx_destroy_image(game->mlx, game->img_collect.img);
	if (game->img_exit.img)
		mlx_destroy_image(game->mlx, game->img_exit.img);
	
	// Libera le animazioni del giocatore
	i = 0;
	while (i < 4)
	{
		if (game->img_player[i].img)
			mlx_destroy_image(game->mlx, game->img_player[i].img);
		i++;
	}
	
	// Libera le animazioni dei nemici
	i = 0;
	while (i < 2)
	{
		if (game->img_enemy[i].img)
			mlx_destroy_image(game->mlx, game->img_enemy[i].img);
		i++;
	}
	
	// Libera la mappa
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	
	// Libera l'array dei nemici
	if (game->enemies)
		free(game->enemies);
	
	// Distruggi la finestra e termina MLX
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	
	// Chiudi e libera mlx (necessario su alcuni sistemi)
	if (game->mlx)
	{
		// Su macOS puoi chiamare:
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	
	exit(0);
	return (0);
}

void	animate_player(t_game *game)
{
	// Cambia il frame del giocatore ogni 10 frame
	if (game->frame_counter % 10 == 0)
		game->player_frame = (game->player_frame + 1) % 4;
}

int	game_loop(t_game *game)
{
	// Incrementa il contatore dei frame
	game->frame_counter++;
	
	// Gestisce le animazioni del giocatore
	animate_player(game);
	
	// Muove i nemici secondo l'intervallo definito
	move_enemies(game);
	
	// Controlla se il gioco è finito
	if (game->game_over)
	{
		mlx_string_put(game->mlx, game->win, 
			(game->map.width * TILE_SIZE) / 2 - 50, 
			(game->map.height * TILE_SIZE) / 2, 
			0x00FF0000, 
			game->collected == game->map.collectibles ? "You Win!" : "Game Over!");
	}
	
	// Aggiorna le animazioni dei nemici
	if (game->frame_counter % 15 == 0)
		game->enemy_frame = (game->enemy_frame + 1) % 2;
	
	// Renderizza il gioco
	render_game(game);
	
	// Mostra il conteggio dei collezionabili raccolti
	char *collect_str = ft_itoa(game->collected);
	char *total_str = ft_itoa(game->map.collectibles);
	
	if (collect_str && total_str)
	{
		char *tmp = ft_strjoin("Collected: ", collect_str);
		if (tmp)
		{
			char *display = ft_strjoin(tmp, "/");
			free(tmp);
			
			if (display)
			{
				tmp = display;
				display = ft_strjoin(tmp, total_str);
				free(tmp);
				
				if (display)
				{
					mlx_string_put(game->mlx, game->win, 10, 40, 0x00FFFFFF, display);
					free(display);
				}
			}
		}
	}
	
	if (collect_str)
		free(collect_str);
	if (total_str)
		free(total_str);
	
	return (0);
}