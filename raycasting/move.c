/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:12:42 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/24 21:12:42 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

static int	is_wall(t_game *game, double x, double y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (game->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	move_forward(t_game *game, double move_speed, int dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + (game->player.dir_x * move_speed * dir);
	new_y = game->player.pos_y + (game->player.dir_y * move_speed * dir);
	if (!is_wall(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_strafe(t_game *game, double move_speed, int dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + (game->player.plane_x * move_speed * dir);
	new_y = game->player.pos_y + (game->player.plane_y * move_speed * dir);
	if (!is_wall(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}
