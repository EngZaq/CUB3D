/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:56:00 by marvin            #+#    #+#             */
/*   Updated: 2025/12/15 19:56:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Define Key Codes (Linux / 42 School Standard)

int	handle_keypress(int key, t_game *game)
{
	double	ms; // Move Speed
	double	rs; // Rot Speed

	ms = 0.1;
	rs = 0.05;
	if (key == KEY_ESC)
		exit_game(game, NULL);
	if (key == KEY_W)
		move_forward(game, ms, 1);
	if (key == KEY_S)
		move_forward(game, ms, -1);
	if (key == KEY_D)
		move_strafe(game, ms, 1);
	if (key == KEY_A)
		move_strafe(game, ms, -1);
	if (key == KEY_RIGHT)
		rotate_player(game, rs); // Negative to look right
	if (key == KEY_LEFT)
		rotate_player(game, -rs);  // Positive to look left
	render_frame(game); 
	return (0);
}