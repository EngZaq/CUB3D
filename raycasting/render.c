/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:12:53 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/24 21:12:53 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_game *game, int tex_x, int tex_y)
{
	int		tex_num;
	char	*dst;
	t_img	*tex;

	if (game->ray.side == 0)
		tex_num = (game->ray.ray_dir_x > 0) ? 3 : 2; // East : West
	else
		tex_num = (game->ray.ray_dir_y > 0) ? 1 : 0; // South : North
	
	// Corrected: accessing game->textures
	tex = &game->textures[tex_num];
	
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	dst = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

int render_frame(t_game *game)
{
    cast_rays(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    return (0);
}