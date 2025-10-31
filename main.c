/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:28:30 by zal-qais          #+#    #+#             */
/*   Updated: 2025/09/06 19:30:31 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char* *argv[])
{
	if (argc != 2)
		error_exit("Usage: ./cub3d <map_file.cub>");
	t_data data;
	if(parse_file(argv[1], &data) == -1)
		error_exit("Error parsing the map file");
		
}

