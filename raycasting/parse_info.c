/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:16:57 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/24 22:14:54 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static char *extract_path(char *line)
{
	char	*path;
	char	*start;
	char	*end;
	int		len;

	start = skip_spaces(line);
	if (!*start)
		return (NULL);
	end = start;
	while (*end && *end != '\n' && *end != ' ' && *end != '\t')
		end++;
	len = end - start;
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	ft_strlcpy(path, start, len + 1);
	return (path);
}

static int parse_color_value(char *str, int *i)
{
	int value;
	int digits;

	value = 0;
	digits = 0;
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		value = value * 10 + (str[*i] - '0');
		(*i)++;
		digits++;
	}
	while (str[*i] == ' ')
		(*i)++;
	if (digits == 0 || value > 255)
		return (-1);
	return (value);
}

int parse_color(char *line)
{
	int r, g, b;
	int i;

	i = 0;
	r = parse_color_value(line, &i);
	if (r < 0 || line[i] != ',')
		return (-1);
	i++;
	g = parse_color_value(line, &i);
	if (g < 0 || line[i] != ',')
		return (-1);
	i++;
	b = parse_color_value(line, &i);
	if (b < 0)
		return (-1);
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (line[i] != '\0')
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int parse_texture(t_game *game, char *line, int index)
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

int parse_element(t_game *game, char *line)
{
	char *trimmed;

	trimmed = skip_spaces(line);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (parse_texture(game, trimmed + 3, 0));
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (parse_texture(game, trimmed + 3, 1));
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (parse_texture(game, trimmed + 3, 2));
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (parse_texture(game, trimmed + 3, 3));
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		game->floor_color = parse_color(trimmed + 2);
		if (game->floor_color == -1)
			return (printf("Error\nInvalid floor color\n"), 0);
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		game->ceil_color = parse_color(trimmed + 2);
		if (game->ceil_color == -1)
			return (printf("Error\nInvalid ceiling color\n"), 0);
	}
	else if (*trimmed && *trimmed != '\n')
		return (2); // Might be map line
	return (1);
}

