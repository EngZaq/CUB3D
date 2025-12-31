/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 22:00:00 by zal-qais          #+#    #+#             */
/*   Updated: 2025/12/31 11:36:01 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*copy_strings(char *result, char *s1, char *s2, size_t len1)
{
	size_t	len2;
	size_t	i;

	len2 = ft_strlen(s2);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		result[i] = s2[i - len1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (free(s1), NULL);
	copy_strings(result, s1, s2, len1);
	free(s1);
	return (result);
}

int	has_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	update_buffer(char **buffer, int i)
{
	char	*new_buffer;

	if ((*buffer)[i])
	{
		new_buffer = ft_strdup(*buffer + i);
		free(*buffer);
		*buffer = new_buffer;
	}
	else
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*extract_line(char **buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = (*buffer)[j];
		j++;
	}
	line[j] = '\0';
	update_buffer(buffer, i);
	return (line);
}
