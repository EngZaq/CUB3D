/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:21:42 by marvin            #+#    #+#             */
/*   Updated: 2025/12/15 20:21:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i])
			free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

void	free_game(t_game *game)
{
	int	j;
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
			free(game->map[i++]);
		free(game->map);
	}
	j = 0;
	while (j < 4)
	{
		if (game->tex_paths[j])
			free(game->tex_paths[j]);
		j++;
	}
}

void	destroy_mlx(t_game *game)
{
	int	i;

	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	exit_game(t_game *game, char *message)
{
	if (message)
		printf("Error\n%s\n", message);
	destroy_mlx(game);
	free_game(game);
	exit(0);
	return (0);
}
