/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:16:13 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/31 11:20:59 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_file(char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		result;

	if (!check_extension(file))
		return (printf("Error\nInvalid file extension (must be .cub)\n"), 0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open file: %s\n", file), 0);
	line = get_next_line(fd);
	while (line)
	{
		result = process_line(game, fd, line);
		if (result != 2)
			return (result != -1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (printf("Error\nNo map found in file\n"), 0);
}

int	parse_map_from_fd(t_game *game, int fd, char *first_line)
{
	char	**map_lines;
	char	*line;
	int		line_count;
	int		result;

	map_lines = NULL;
	line_count = 0;
	if (!add_line_to_array(&map_lines, &line_count, first_line))
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!add_line_to_array(&map_lines, &line_count, line))
		{
			free(line);
			free_lines(map_lines);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	result = store_map(game, map_lines);
	free_lines(map_lines);
	return (result);
}

int	store_map(t_game *game, char **raw_lines)
{
	int		height;
	int		width;
	int		i;

	height = count_map_lines(raw_lines);
	if (height == 0)
		return (printf("Error\nNo map found\n"), 0);
	width = get_max_width(raw_lines);
	game->map = malloc(sizeof(char *) * (height + 1));
	if (!game->map)
		return (0);
	i = 0;
	while (i < height)
	{
		game->map[i] = pad_line(raw_lines[i], width);
		if (!game->map[i])
			return (0);
		i++;
	}
	game->map[height] = NULL;
	game->map_height = height;
	game->map_width = width;
	return (1);
}

int	count_map_lines(char **lines)
{
	int	count;

	count = 0;
	while (lines && lines[count])
		count++;
	return (count);
}

char	*remove_newline(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
