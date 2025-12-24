/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:16:38 by marvin            #+#    #+#             */
/*   Updated: 2025/12/15 20:16:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pick_texture(t_game *game)
{
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		return (3);
	else if (game->ray.side == 0)
		return (2);
	else if (game->ray.side == 1 && game->ray.ray_dir_y > 0)
		return (1);
	else
		return (0);
}

void	draw_stripe(t_game *game, int x)
{
	int		y;
	t_strip	strip;

	strip.curr_tex = &game->textures[pick_texture(game)];
	strip.tex_x = (int)(game->ray.wall_x * (double)strip.curr_tex->width);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		strip.tex_x = strip.curr_tex->width - strip.tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		strip.tex_x = strip.curr_tex->width - strip.tex_x - 1;
	strip.step = 1.0 * strip.curr_tex->height / game->ray.line_height;
	strip.tex_pos = (game->ray.draw_start - HEIGHT / 2
			+ game->ray.line_height / 2) * strip.step;
	y = -1;
	while (++y < game->ray.draw_start)
		put_pixel(game, x, y, game->ceil_color);
	y = game->ray.draw_start - 1;
	while (++y < game->ray.draw_end)
	{
		strip.tex_y = (int)strip.tex_pos % strip.curr_tex->height;
		strip.tex_pos += strip.step;
		put_pixel(game, x, y, get_texture_color(game, strip.tex_x, strip.tex_y));
	}
	y = game->ray.draw_end - 1;
	while (++y < HEIGHT)
		put_pixel(game, x, y, game->floor_color);
}

void	line_height(t_game *game)
{
	if (game->ray.perp_wall_dist < 0.00001)
		game->ray.perp_wall_dist = 0.00001;
	game->ray.line_height = (int)(HEIGHT / game->ray.perp_wall_dist);
	game->ray.draw_start = -game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.draw_end >= HEIGHT)
		game->ray.draw_end = HEIGHT - 1;
}

void	calc_wall_x(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.wall_x = game->player.pos_y + game->ray.perp_wall_dist
			* game->ray.ray_dir_y;
	else
		game->ray.wall_x = game->player.pos_x + game->ray.perp_wall_dist
			* game->ray.ray_dir_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
}

void	perp_dist(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.side_dist_x
				- game->ray.delta_dist_x);
	else
		game->ray.perp_wall_dist = (game->ray.side_dist_y
				- game->ray.delta_dist_y);
}

void	core_dda(t_game *game)
{
	while (game->ray.hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->map[game->ray.map_y][game->ray.map_x] == '1')
			game->ray.hit = 1;
	}
}

void	side_step_stuff(t_game *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
	}
}

void	init_ray(t_game *game, int x)
{
	game->ray.camera_x = 2 * x / (double)WIDTH - 1;
	game->ray.ray_dir_x = game->player.dir_x + game->player.plane_x
		* game->ray.camera_x;
	game->ray.ray_dir_y = game->player.dir_y + game->player.plane_y
		* game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	game->ray.hit = 0;
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, x);
		side_step_stuff(game);
		core_dda(game);
		perp_dist(game);
		calc_wall_x(game);
		line_height(game);
		draw_stripe(game, x);
		x++;
	}
}