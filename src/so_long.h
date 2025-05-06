#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define TILE_SIZE 64
# define ENEMY_MOVE_INTERVAL 50 // Nemici si muovono ogni 50 frame

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		collectibles;
	int		enemies;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		dir_x;
	int		dir_y;
}	t_enemy;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		img_wall;
	t_img		img_floor;
	t_img		img_collect;
	t_img		img_exit;
	t_img		img_player[4];  // Array per le animazioni del giocatore
	t_img		img_enemy[2];   // Array per le animazioni del nemico
	int			player_frame;   // Frame corrente per l'animazione del giocatore
	int			enemy_frame;    // Frame corrente per l'animazione del nemico
	int			collected;
	int			moves;
	int			game_over;
	int			frame_counter;  // Contatore di frame per le animazioni
	t_enemy		*enemies;       // Array di nemici
}	t_game;

int		check_extension(char *filename);
int		read_map(t_map *map, char *filename);
int		check_map_structure(t_map *map);
int		check_map_elements(t_map *map);
int		check_valid_path(t_map *map);
char	**copy_map(t_map *map);
void	flood_fill(char **map, int x, int y, t_map *original);
int		check_reachable(char **filled_map, t_map *original);
int		validate_map(t_map *map, char *filename);
int		error_message(char *msg);
void	free_temp_map(char **map, int height);

// Inizializzazione e cleanup
int		init_game(t_game *game, char *map_file);
void	init_images(t_game *game);
void	cleanup_game(t_game *game);

// Rendering
void	render_game(t_game *game);
void	render_moves(t_game *game);
void	put_image(t_game *game, void *img, int x, int y);

// Input e movimento
int		key_press(int keycode, t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
void	move_enemies(t_game *game);
int		check_collision(t_game *game, int x, int y);

// Gestione eventi
int		close_window(t_game *game);
int		game_loop(t_game *game);

//GET NEXT LINE
typedef struct s_chunk
{
	char			*data;
	size_t			size;
	struct s_chunk	*next;
}	t_chunk;

typedef struct s_fdata
{
	char	buffer[BUFFER_SIZE];
	size_t	start;
	size_t	end;
	t_chunk	*head;
	t_chunk	*tail;
}	t_fdata;

char	*get_next_line(int fd);
t_fdata	*ft_newindex(void);
t_fdata	*ft_updateindex(t_fdata *index, int fd);
int		ft_read_and_collect(t_fdata *index, int *found_newline);
char	*ft_join_chunks(t_fdata *index);
void	ft_free_chunks(t_fdata *index);
void	ft_add_chunk(t_fdata *index, const char *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif