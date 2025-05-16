/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:55:54 by rpontici          #+#    #+#             */
/*   Updated: 2025/05/16 19:55:55 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define TILE_SIZE 64
# define ENEMY_MOVE_INTERVAL 50 // Nemici si muovono ogni 50 frame

# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	int				exit_x;
	int				exit_y;
	int				collectibles;
	int				enemies;
}					t_map;

typedef struct s_img
{
	void			*img;
	int				width;
	int				height;
}					t_img;

typedef struct s_enemy
{
	int				x;
	int				y;
	int				dir_x;
	int				dir_y;
}					t_enemy;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_img			img_wall;
	t_img			img_floor;
	t_img			img_collect;
	t_img			img_exit;
	t_img			img_player[4];
	t_img			img_enemy[2];
	int				player_frame;
	int				enemy_frame;
	int				collected;
	int				moves;
	int				game_over;
	int				frame_counter;
	t_enemy			*enemies;
}					t_game;

int					check_extension(char *filename);
int					read_map(t_map *map, char *filename);
int					check_map_structure(t_map *map);
int					check_map_elements(t_map *map);
int					check_valid_path(t_map *map);
char				**copy_map(t_map *map);
void				flood_fill(char **map, int x, int y, t_map *original);
int					check_reachable(char **filled_map, t_map *original);
int					validate_map(t_map *map, char *filename);
int					error_message(char *msg);
void				free_temp_map(char **map, int height);
int					init_game(t_game *game, char *map_file);
void				init_images(t_game *game);
int					init_enemies(t_game *game);
void				cleanup_game(t_game *game);
void				render_game(t_game *game);
void				render_moves(t_game *game);
void				put_image(t_game *game, void *img, int x, int y);
int					key_press(int keycode, t_game *game);
void				move_player(t_game *game, int new_x, int new_y);
void				move_enemies(t_game *game);
int					check_collision(t_game *game, int x, int y);
void				animate_player(t_game *game);
int					check_enemy_collision(t_game *game, int x, int y);
int					is_valid_position(t_game *game, int new_x, int new_y);
int					read_map_line(t_map *map, int fd);
int					close_window(t_game *game);
int					game_loop(t_game *game);
void				count_enemies(t_game *game);

// GET NEXT LINE
typedef struct s_chunk
{
	char			*data;
	size_t			size;
	struct s_chunk	*next;
}					t_chunk;

typedef struct s_fdata
{
	char			buffer[BUFFER_SIZE];
	size_t			start;
	size_t			end;
	t_chunk			*head;
	t_chunk			*tail;
}					t_fdata;

char				*get_next_line(int fd);
t_fdata				*ft_newindex(void);
t_fdata				*ft_updateindex(t_fdata *index, int fd);
int					ft_read_and_collect(t_fdata *index, int *found_newline);
char				*ft_join_chunks(t_fdata *index);
void				ft_free_chunks(t_fdata *index);
void				ft_add_chunk(t_fdata *index, const char *src, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);

#endif