/* ************************************************************************** */
/* main.c                                             :+:      :+:    :+:   */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

// Simple wrapper to match the prototype needed for mlx_hook 17
int	close_window_cross(t_game *game)
{
	exit_game(game, NULL);
	return (0);
}

void	init_test_data(t_game *game)
{
	int		i;
	
	game->map_width = 10;
	game->map_height = 10;

	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	i = 0;
	while (i < game->map_height)
	{
		game->map[i] = malloc(sizeof(char) * (game->map_width + 1));
		i++;
	}
	game->map[game->map_height] = NULL;

	strcpy(game->map[0], "1111111111");
	strcpy(game->map[1], "1000000001");
	strcpy(game->map[2], "1000000001");
	strcpy(game->map[3], "1000110001");
	strcpy(game->map[4], "1000110001");
	strcpy(game->map[5], "1000000001");
	strcpy(game->map[6], "1001000001");
	strcpy(game->map[7], "1001000001");
	strcpy(game->map[8], "1000000001");
	strcpy(game->map[9], "1111111111");

	game->player.pos_x = 5.5;
	game->player.pos_y = 5.5;
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;

	// FIX: Use tex_paths (matching the header)
	game->tex_paths[0] = "./textures/north.xpm";
	game->tex_paths[1] = "./textures/south.xpm";
	game->tex_paths[2] = "./textures/west.xpm";
	game->tex_paths[3] = "./textures/east.xpm";

	game->floor_color = 0x333333;
	game->ceil_color = 0x87CEEB;
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	memset(&game, 0, sizeof(t_game));

	printf("Initializing test data...\n");
	init_test_data(&game);

	printf("Initializing MLX...\n");
	if (init_mlx(&game) != 0)
		return (1);

	printf("Rendering first frame...\n");
	render_frame(&game);

	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_window_cross, &game);
	
	// UNCOMMENTED THIS so your game loops:
	mlx_loop_hook(game.mlx, render_frame, &game); 

	printf("Starting Loop...\n");
	mlx_loop(game.mlx);

	return (0);
}
