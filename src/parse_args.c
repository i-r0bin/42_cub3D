#include "cub3d.h"

int	parse_args(t_data *data, char **av)
{
    int     fd;
    char    *format;
    int     ret;

    format = ft_strrchr(av[1], '.');
    if (!format || ft_strlen(format) != 4 || ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4) != 0)
        return (err_msg("Invalid file extension\nError", EINVAL));
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (err_msg("Could not open file\nError", errno));
    ret = parse_file(data, fd);
    close(fd);
    return (ret);
}

int	parse_file(t_data *data, int fd)
{
    char *line;
    int ret;

    line = get_next_line(fd);
    while (line)
    {
        ret = parse_line(data, line);
        free(line);
        if (ret != 0)
            return (ret);
        line = get_next_line(fd);
    }
    if (line)
        free(line);
    if (!data->map)
        return (err_msg("Invalid map\nError", ENOEXEC));
    return (0);
}

int	parse_line(t_data *data, char *line)
{
    if (line[0] == 'N' && line[1] == 'O')
        return (parse_texture(data, line, 0));
    else if (line[0] == 'S' && line[1] == 'O')
        return (parse_texture(data, line, 1));
    else if (line[0] == 'W' && line[1] == 'E')
        return (parse_texture(data, line, 2));
    else if (line[0] == 'E' && line[1] == 'A')
        return (parse_texture(data, line, 3));
    else if (line[0] == 'S')
        return (parse_texture(data, line, 4));
    else if (line[0] == 'F')
        return (parse_color(data, line, 0));
    else if (line[0] == 'C')
        return (parse_color(data, line, 1));
    else if (line[0] == '1' || line[0] == ' ')
        return (parse_map(data, line));
    else if (line[0] != '\0' && line[0] != '\n')
        return (err_msg("Invalid map\nError", ENOEXEC));
    return (0);
}

int	parse_texture(t_data *data, char *line, int i)
{
    int j;

    j = 2;
    while (line[j] == ' ')
        j++;
    data->wall_textures[i] = ft_strdup(line + j);
    return (0);
}

int	parse_color(t_data *data, char *line, int i)
{
    int j;
    int r;
    int g;
    int b;

    j = 1;
    while (line[j] == ' ')
        j++;
    r = ft_atoi(line + j);
    while (ft_isdigit(line[j]))
        j++;
    g = ft_atoi(line + j + 1);
    while (ft_isdigit(line[j]))
        j++;
    b = ft_atoi(line + j + 1);
    data->floor_color = (i == 0) ? ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff) : data->floor_color;
    data->ceiling_color = (i == 1) ? ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff) : data->ceiling_color;
    return (0);
}
