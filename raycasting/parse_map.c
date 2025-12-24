/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 22:00:00 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/24 22:14:54 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int count_map_lines(char **lines)
{
	int count;

	count = 0;
	while (lines && lines[count])
		count++;
	return (count);
}

static char *remove_newline(char *line)
{
	int len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static int get_max_width(char **lines)
{
	int max;
	int len;
	int i;

	max = 0;
	i = 0;
	while (lines && lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char *pad_line(char *line, int width)
{
	char	*padded;
	int		len;
	int		i;

	len = ft_strlen(line);
	padded = malloc(width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[i] = '\0';
	return (padded);
}

int store_map(t_game *game, char **raw_lines)
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

static int add_line_to_array(char ***lines, int *count, char *line)
{
	char **new_lines;
	int i;

	new_lines = malloc(sizeof(char *) * (*count + 2));
	if (!new_lines)
		return (0);
	i = 0;
	while (i < *count)
	{
		new_lines[i] = (*lines)[i];
		i++;
	}
	new_lines[*count] = ft_strdup(remove_newline(line));
	new_lines[*count + 1] = NULL;
	free(*lines);
	*lines = new_lines;
	(*count)++;
	return (1);
}

static void free_lines(char **lines)
{
	int i;

	if (!lines)
		return;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

int parse_map_from_fd(t_game *game, int fd, char *first_line)
{
	char	**map_lines;
	char	*line;
	int		line_count;
	int		result;

	map_lines = NULL;
	line_count = 0;
	// Add the first map line
	if (!add_line_to_array(&map_lines, &line_count, first_line))
		return (0);
	// Read remaining lines
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

int parse_file(char *file, t_game *game)
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
		result = parse_element(game, line);
		if (result == 0)
		{
			free(line);
			close(fd);
			return (0);
		}
		if (result == 2) // Found map line
		{
			if (has_data_missing(game))
			{
				free(line);
				close(fd);
				return (printf("Error\nMissing texture or color before map\n"), 0);
			}
			result = parse_map_from_fd(game, fd, line);
			free(line);
			close(fd);
			return (result);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (printf("Error\nNo map found in file\n"), 0);
}
