/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:12:36 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/24 21:12:36 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Wrapper to match the prototype needed for mlx_hook 17
int	close_window_cross(t_game *game)
{
	exit_game(game, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	// Initialize game structure
	init_game_struct(&game);
	
	// Parse the .cub file
	if (!parse_file(argv[1], &game))
		return (1);
	
	// Validate the map
	if (!validate_map(&game))
	{
		free_game(&game);
		return (1);
	}
	
	// Initialize MLX and window
	if (init_mlx(&game) != 0)
	{
		printf("Error\nFailed to initialize MLX\n");
		free_game(&game);
		return (1);
	}
	
	// Render first frame
	render_frame(&game);
	
	// Setup hooks
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_window_cross, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	
	// Start the game loop
	mlx_loop(game.mlx);
	
	return (0);
}
