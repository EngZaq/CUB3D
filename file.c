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

int	check_file_extension(char *filename)
{
	char	*extension;

	if (!filename)
		return (-1);
	extension = ft_strrchr(filename, '.');
	if (!extension)
	{
		perror("no extension found");
		return (-1);
	}
	if (ft_strncmp(extension, ".cub", 5) == 0)
		return (0);
	perror("invalid file extension");
	return (-1);
}

#include "cub3d.h"

char *read_line(int fd)
{
    char buffer[2];
    char *line;
    int bytes;
    char *temp;
    int len;
    int i;

    line = NULL;
    len = 0;
    while ((bytes = read(fd, buffer, 1)) > 0)
    {
        i = 0;
        buffer[1] = '\0';
        temp = malloc(len + 2);
        if (!temp)
            return (NULL);
        while ( i < len)
        {
            if (line)
                temp[i] = line[i];
            else
                temp[i] = 0;
            i++;
        }
        temp[len] = buffer[0];
        temp[len + 1] = '\0';
        free(line);
        line = temp;
        len++;
        if (buffer[0] == '\n')
            break;
    }
    return (line);
}
