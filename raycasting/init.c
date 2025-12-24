/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:17:26 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/24 21:19:55 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game_struct(t_game *game)
{
    ft_memset(game, 0, sizeof(t_game));
    game->floor_color = -1;
    game->ceil_color = -1;
    
}