#include "cub3d.h"

int parse_file(char *filename, t_data *data)
{
    int fd;
    char *line;

    if (check_file_extension(filename) == -1)
        error_exit("Invalid file extension (expected .cub)");

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        error_exit("Failed to open file");

    while ((line = read_line(fd)))
    {
        if (parse_config_line(line, data))
        {
            parse_map(fd, line, data);
            break;
        }
        free(line);
    }
    close(fd);
    return (0);
}
