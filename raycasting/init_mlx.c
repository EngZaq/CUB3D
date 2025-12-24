/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:11:40 by marvin            #+#    #+#             */
/*   Updated: 2025/12/14 13:11:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void    ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd >= 0 && fd <= 1023)
	{
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	init_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
				game->tex_paths[i], &game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
			exit_game(game, "Error\nFailed to load texture\n");
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (-1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
	{
		free(game->mlx);
		return (-1);
	}
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
	{
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
		return (-1);
	}
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	game->img.width = WIDTH;
	game->img.height = HEIGHT;
	init_texture(game);
	return (0);
}
