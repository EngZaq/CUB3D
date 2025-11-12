#include "cub3d.h"

static void 
parse_texture(char *line, t_data *data)
{
    char *path = line + 2;
    while (*path == ' ')
        path++;
    if (strncmp(line, "NO", 2) == 0)
        data->no_texture = strdup(path);
    else if (strncmp(line, "SO", 2) == 0)
        data->so_texture = strdup(path);
    else if (strncmp(line, "WE", 2) == 0)
        data->we_texture = strdup(path);
    else if (strncmp(line, "EA", 2) == 0)
        data->ea_texture = strdup(path);
}

static int rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static void parse_color(char *line, t_data *data)
{
    int r, g, b;

    if (line[0] == 'F')
        // read from file
    else if (line[0] == 'C')
        // read form file
}

int parse_config_line(char *line, t_data *data)
{
    if (!line || line[0] == '\n')
        return (0);
    if (!strncmp(line, "NO", 2) || !strncmp(line, "SO", 2)
        || !strncmp(line, "WE", 2) || !strncmp(line, "EA", 2))
        parse_texture(line, data);
    else if (line[0] == 'F' || line[0] == 'C')
        parse_color(line, data);
    else
        return (1); 
    return (0);
}
