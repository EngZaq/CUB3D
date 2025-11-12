#include "cub3d.h"

char **append_line(char **map, char *line, int *count)
{
    char **new_map;
    int i = 0;

    new_map = malloc(sizeof(char *) * (*count + 2));
    if (!new_map)
        return (NULL);
    while (i < *count)
    {
        new_map[i] = map[i];
        i++;
    }
    new_map[i] = strdup(line);
    new_map[i + 1] = NULL;
    free(map);
    (*count)++;
    return (new_map);
}

int parse_map(int fd, char *first_line, t_data *data)
{
    char *line;
    int map_line_count = 0;

    data->map = NULL;
    data->map = append_line(data->map, first_line, &map_line_count);
    while ((line = read_line(fd)))
    {
        if (line[0] == '\n')
        {
            free(line);
            continue;
        }
        data->map = append_line(data->map, line, &map_line_count);
        free(line);
    }
    data->map_height = map_line_count;
    data->map_width = strlen(data->map[0]);
    return (0);
}
