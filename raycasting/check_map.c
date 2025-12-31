/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:21:53 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/31 10:50:43 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static int	set_player(t_game *game, int x, int y, char dir)
{
	if (game->player.dir_x != 0 || game->player.dir_y != 0)
	{
		printf("Error\nMultiple player spawn points found\n");
		return (0);
	}
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	game->map[y][x] = '0';
	return (1);
}

static int	check_valid_chars(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
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

static int	check_cell_surrounded(t_game *game, int x, int y)
{
	if (x == 0 || y == 0 || x >= game->map_width - 1
		|| y >= game->map_height - 1)
		return (0);
	if (game->map[y - 1][x] == ' ' || game->map[y + 1][x] == ' ')
		return (0);
	if (game->map[y][x - 1] == ' ' || game->map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	check_walls(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			c = game->map[y][x];
			if (c == '0')
			{
				if (!check_cell_surrounded(game, x, y))
				{
					printf("Error\nMap is not closed/surrounded by walls\n");
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!game->map || game->map_height == 0 || game->map_width == 0)
	{
		printf("Error\nEmpty or invalid map\n");
		return (0);
	}
	if (!check_valid_chars(game))
		return (0);
	if (!check_walls(game))
		return (0);
	return (1);
}
