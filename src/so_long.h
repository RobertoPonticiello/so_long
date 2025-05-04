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