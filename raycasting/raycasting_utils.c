/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:02:58 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/31 11:09:13 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
