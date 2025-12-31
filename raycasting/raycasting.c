/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:16:38 by marvin            #+#    #+#             */
/*   Updated: 2025/12/15 20:16:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pick_texture(t_game *game)
{
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		return (3);
	else if (game->ray.side == 0)
		return (2);
	else if (game->ray.side == 1 && game->ray.ray_dir_y > 0)
		return (1);
	else
		return (0);
}

static void	draw_stripe_pixels(t_game *game, int x, t_strip *strip)
{
	int	y;

	y = -1;
	while (++y < game->ray.draw_start)
		put_pixel(game, x, y, game->ceil_color);
	y = game->ray.draw_start - 1;
	while (++y < game->ray.draw_end)
	{
		strip->tex_y = (int)strip->tex_pos % strip->curr_tex->height;
		strip->tex_pos += strip->step;
		put_pixel(game, x, y,
			get_texture_color(game, strip->tex_x, strip->tex_y));
	}
	y = game->ray.draw_end - 1;
	while (++y < HEIGHT)
		put_pixel(game, x, y, game->floor_color);
}

void	draw_stripe(t_game *game, int x)
{
	t_strip	strip;

	strip.curr_tex = &game->textures[pick_texture(game)];
	strip.tex_x = (int)(game->ray.wall_x * (double)strip.curr_tex->width);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		strip.tex_x = strip.curr_tex->width - strip.tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		strip.tex_x = strip.curr_tex->width - strip.tex_x - 1;
	strip.step = 1.0 * strip.curr_tex->height / game->ray.line_height;
	strip.tex_pos = (game->ray.draw_start - HEIGHT / 2
			+ game->ray.line_height / 2) * strip.step;
	draw_stripe_pixels(game, x, &strip);
}

void	line_height(t_game *game)
{
	if (game->ray.perp_wall_dist < 0.00001)
		game->ray.perp_wall_dist = 0.00001;
	game->ray.line_height = (int)(HEIGHT / game->ray.perp_wall_dist);
	game->ray.draw_start = -game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.draw_end >= HEIGHT)
		game->ray.draw_end = HEIGHT - 1;
}

void	calc_wall_x(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.wall_x = game->player.pos_y + game->ray.perp_wall_dist
			* game->ray.ray_dir_y;
	else
		game->ray.wall_x = game->player.pos_x + game->ray.perp_wall_dist
			* game->ray.ray_dir_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
}
