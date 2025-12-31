/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 22:00:00 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/31 11:20:09 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_max_width(char **lines)
{
	int	max;
	int	len;
	int	i;

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

char	*pad_line(char *line, int width)
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

int	add_line_to_array(char ***lines, int *count, char *line)
{
	char	**new_lines;
	int		i;

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

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

int	process_line(t_game *game, int fd, char *line)
{
	int	result;

	result = parse_element(game, line);
	if (result == 0)
	{
		free(line);
		close(fd);
		return (-1);
	}
	if (result == 2)
	{
		if (has_data_missing(game))
		{
			free(line);
			close(fd);
			return (printf("Error\nMissing texture or color before map\n"), -1);
		}
		result = parse_map_from_fd(game, fd, line);
		free(line);
		close(fd);
		return (result);
	}
	return (2);
}
