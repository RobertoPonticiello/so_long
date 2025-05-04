#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include "libft.h"

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
}	t_map;

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

#endif