#include "cub3d.h"

int parse_file(char *filename, t_data *data)
{
    if (check_file_extension(filename) == -1)
        return -1;
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;

    close(fd);
    return 0;
}