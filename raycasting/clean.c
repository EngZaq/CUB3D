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

/**
 * @brief Frees the 2D map array.
 * Checks for NULLs to prevent segfaults during partial initialization failures.
 */
void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	// Use map_height if valid, otherwise count until NULL if unsure
	while (i < game->map_height)
	{
		if (game->map[i])
			free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

/**
 * @brief Main cleanup function for non-MLX memory.
 * Frees the map and texture paths (if your parser allocated them).
 */
void	free_game(t_game *game)
{
	free_map(game);

	// NOTE: Only uncomment the loop below if your partner's parser 
	// uses malloc/ft_strdup for the texture paths. 
	// In our test 'main.c', these are static strings, so we DO NOT free them.
	
	/*
	int i = 0;
	while (i < 4)
	{
		if (game->tex_paths[i])
			free(game->tex_paths[i]);
		i++;
	}
	*/
}

/**
 * @brief Destroys MLX images, window, and display.
 * This handles the graphical memory specifically.
 */
void	destroy_mlx(t_game *game)
{
	int	i;

	// 1. Destroy the Main Image Buffer
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	
	// 2. Destroy Wall Textures
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}

	// 3. Destroy Window
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);

	// 4. Destroy Display & Free MLX Ptr (Linux specific, but good for 42)
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/**
 * @brief Unified exit function.
 * Prints an error message (if any), cleans everything, and exits.
 */
int	exit_game(t_game *game, char *message)
{
	if (message)
		printf("Error\n%s\n", message);
	
	// Clean up graphics first
	destroy_mlx(game);
	
	// Clean up standard memory
	free_game(game);
	
	exit(0);
	return (0);
}