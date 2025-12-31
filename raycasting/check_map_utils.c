/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:00:00 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/31 11:43:44 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_dir(t_game *game, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_player_dir_ns(game, dir);
	else if (dir == 'E' || dir == 'W')
		set_player_dir_ew(game, dir);
}

int	set_player(t_game *game, int x, int y, char dir)
{
	if (game->player.dir_x != 0 || game->player.dir_y != 0)
	{
		printf("Error\nMultiple player spawn points found\n");
		return (0);
	}
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	set_player_dir(game, dir);
	game->map[y][x] = '0';
	return (1);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	check_char_at(t_game *game, int x, int y)
{
	char	c;

	c = game->map[y][x];
	if (!is_valid_char(c))
	{
		printf("Error\nInvalid character '%c' in map\n", c);
		return (0);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!set_player(game, x, y, c))
			return (0);
	}
	return (1);
}

int	check_valid_chars(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (!check_char_at(game, x, y))
				return (0);
			x++;
		}
		y++;
	}
	if (game->player.dir_x == 0 && game->player.dir_y == 0)
	{
		printf("Error\nNo player spawn point found\n");
		return (0);
	}
	return (1);
}
