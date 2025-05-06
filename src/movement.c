#include "so_long.h"

int	check_enemy_collision(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->map.enemies)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->game_over)
		return ;
		
	if (new_x < 0 || new_y < 0 || new_x >= game->map.width
		|| new_y >= game->map.height)
		return ;
		
	if (game->map.grid[new_y][new_x] == '1')
		return ;
		
	// Controlla collisione con i nemici
	if (check_enemy_collision(game, new_x, new_y))
	{
		game->game_over = 1;
		ft_putstr_fd("Game Over! You hit an enemy.\n", 1);
		return ;
	}
	
	// Gestione dei collezionabili
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->map.grid[new_y][new_x] = '0';
		game->collected++;
	}
	
	// Gestione dell'uscita
	if (game->map.grid[new_y][new_x] == 'E')
	{
		if (game->collected == game->map.collectibles)
		{
			game->game_over = 1;
			ft_putstr_fd("You win!\n", 1);
		}
		else
			return ;
	}
	
	// Aggiorna la posizione del giocatore
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	game->map.grid[new_y][new_x] = 'P';
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	
	// Incrementa il contatore delle mosse
	game->moves++;
	
	// Aggiorna l'animazione del giocatore
	game->player_frame = (game->player_frame + 1) % 4;
}

int	check_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (1);
	return (game->map.grid[y][x] == '1');
}

void	move_enemy(t_game *game, int idx)
{
	int	new_x;
	int	new_y;

	new_x = game->enemies[idx].x + game->enemies[idx].dir_x;
	new_y = game->enemies[idx].y + game->enemies[idx].dir_y;
	
	// Se c'è un muro, cambia direzione
	if (check_wall(game, new_x, new_y))
	{
		game->enemies[idx].dir_x *= -1;
		game->enemies[idx].dir_y *= -1;
		return ;
	}
	
	// Muovi il nemico
	game->enemies[idx].x = new_x;
	game->enemies[idx].y = new_y;
	
	// Controlla se il nemico ha colpito il giocatore
	if (new_x == game->map.player_x && new_y == game->map.player_y)
	{
		game->game_over = 1;
		ft_putstr_fd("Game Over! An enemy got you.\n", 1);
	}
}

void	move_enemies(t_game *game)
{
	int	i;

	if (game->frame_counter % ENEMY_MOVE_INTERVAL != 0)
		return ;
		
	i = 0;
	while (i < game->map.enemies)
	{
		move_enemy(game, i);
		i++;
	}
	
	// Aggiorna il frame dell'animazione nemico
	game->enemy_frame = (game->enemy_frame + 1) % 2;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53) // ESC key
		close_window(game);
		
	if (game->game_over)
		return (0);
		
	if (keycode == 13 || keycode == 126) // W o freccia su
		move_player(game, game->map.player_x, game->map.player_y - 1);
	else if (keycode == 1 || keycode == 125) // S o freccia giù
		move_player(game, game->map.player_x, game->map.player_y + 1);
	else if (keycode == 0 || keycode == 123) // A o freccia sinistra
		move_player(game, game->map.player_x - 1, game->map.player_y);
	else if (keycode == 2 || keycode == 124) // D o freccia destra
		move_player(game, game->map.player_x + 1, game->map.player_y);
		
	return (0);
}