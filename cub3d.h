#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
// #include <mlx.h>
// #include "libft/libft.h"


typedef struct s_data{
    char **map;

    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;

    int     floor_color;
    int     ceiling_color;

    int    player_x;
    int    player_y;
    char   player_dir;

    int    map_width;
    int    map_height;

	void	*mlx;
	void	*win;
} t_data;

void error_exit(char *message);
int parse_file(char *filename, t_data *data);
int check_file_extension(char *filename);

# endif
