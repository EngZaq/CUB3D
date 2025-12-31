/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_information.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:23:43 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/31 11:35:40 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		temp[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	while (!has_newline(buffer))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = ft_strjoin_free(buffer, temp);
	}
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (extract_line(&buffer));
}

int	parse_texture(t_game *game, char *line, int index)
{
	if (game->tex_paths[index] != NULL)
	{
		printf("Error\nDuplicate texture identifier\n");
		return (0);
	}
	game->tex_paths[index] = extract_path(line);
	if (!game->tex_paths[index])
	{
		printf("Error\nFailed to extract texture path\n");
		return (0);
	}
	return (1);
}

int	parse_color_element(t_game *game, char *trimmed)
{
	if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		game->floor_color = parse_color(trimmed + 2);
		if (game->floor_color == -1)
			return (printf("Error\nInvalid floor color\n"), 0);
		return (1);
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		game->ceil_color = parse_color(trimmed + 2);
		if (game->ceil_color == -1)
			return (printf("Error\nInvalid ceiling color\n"), 0);
		return (1);
	}
	else if (*trimmed && *trimmed != '\n')
		return (2);
	return (1);
}

int	parse_element(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (parse_texture(game, trimmed + 3, 0));
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (parse_texture(game, trimmed + 3, 1));
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (parse_texture(game, trimmed + 3, 2));
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (parse_texture(game, trimmed + 3, 3));
	return (parse_color_element(game, trimmed));
}
