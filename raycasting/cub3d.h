/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:14:04 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/24 21:14:04 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "Libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1080
# define HEIGHT 720

// Key Codes
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_strip
{
	int		tex_y;
	int		tex_x;
	double	step;
	double	tex_pos;
	t_img	*curr_tex;
}	t_strip;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		textures[4];
	char		**map;
	int			map_width;
	int			map_height;
	char		*tex_paths[4];
	int			floor_color;
	int			ceil_color;
	t_player	player;
	t_ray		ray;
}	t_game;

// Render
void	put_pixel(t_game *game, int x, int y, int color);
int		get_texture_color(t_game *game, int tex_x, int tex_y);

// Init & Clean
int		init_mlx(t_game *game);
void	init_game_struct(t_game *game);
int		exit_game(t_game *game, char *msg);
void	free_game(t_game *game);
void	free_map(t_game *game);

// Parsing
int		parse_file(char *file, t_game *game);
int		check_extension(char *file);
int		is_map_line(char *line);
int		validate_map(t_game *game);
int		parse_element(t_game *game, char *line);
int		has_data_missing(t_game *game);
void	free_split(char **split);
int		get_array_len(char **arr);
char	*get_next_line(int fd);

// Game Logic
int		render_frame(t_game *game);
void	cast_rays(t_game *game);
int		handle_keypress(int key, t_game *game);
void	move_forward(t_game *game, double speed, int dir);
void	move_strafe(t_game *game, double speed, int dir);
void	rotate_player(t_game *game, double rot_speed);

#endif