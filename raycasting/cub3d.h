/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:14:51 by marvin            #+#    #+#             */
/*   Updated: 2025/12/15 20:14:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h" // Ensure this path matches your folder

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_ray {
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}	t_ray;

typedef struct s_strip{
	int		tex_y;
	int		tex_x;
	double	step;
	double	tex_pos;
	t_img	*curr_tex;
}	t_strip;


typedef struct s_player {
	double	pos_x; // Renamed to pos_x to match your .c files
	double	pos_y; // Renamed to pos_y
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_ray		ray;
	char		**map;
	int			map_width;
	int			map_height;
	
	// Textures
	char		*tex_paths[4]; // Stores the file paths ("./north.xpm")
	t_img		textures[4];   // Stores the actual loaded images
	
	int			floor_color;
	int			ceil_color;
}	t_game;

typedef struct s_data{
	char **map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		map_width;
	int		map_height;
	void	*mlx;
	void	*win;
} t_data;

# define WIDTH 100
# define HEIGHT 100
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

void	error_exit(char *message);
int		parse_file(char *filename, t_data *data);
int		check_file_extension(char *filename);

// Prototypes
int		exit_game(t_game *game, char *message);
void	destroy_mlx(t_game *game);
int		init_mlx(t_game *game);
void	init_test_data(t_game *game); // Used in main

// Hooks
int		handle_keypress(int key, t_game *game);
int		close_window_cross(t_game *game); // Renamed for clarity

// Raycasting & Render
void	cast_rays(t_game *game);
int		render_frame(t_game *game);
void	draw_stripe(t_game *game, int x);
int		get_texture_color(t_game *game, int tex_x, int tex_y);
void	put_pixel(t_game *game, int x, int y, int color);

// Movement
void	move_strafe(t_game *game, double move_speed, int dir);
void	move_forward(t_game *game, double move_speed, int dir);
void	rotate_player(t_game *game, double rot_speed);

#endif