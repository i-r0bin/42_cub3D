#include "cub3d.h"

int	parse_args(t_data *data, char **av)
{
    int     fd;
    char    *format;

    format = ft_strrchr(av[1], '.');
    if (!format || ft_strlen(format) != 4 || ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4) != 0)
        handle_error(data, EINVAL, "Invalid file format. Only .cub files are accepted.");
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        handle_error(data, errno, "Failed to open file.");
    parse_file(data, fd);
    close(fd);
    return (0);
}

int	parse_file(t_data *data, int fd)
{
    char *line;
    int end_map;

    end_map = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (*line_start(line) == '\n' && data->map)
            end_map = 1;
        else if (*line_start(line) == '1' && end_map == 1)
            handle_error(data, ENOEXEC, "Invalid map.");
        parse_line(data, line);
        free(line);
        line = get_next_line(fd);
    }
    if (!data->map)
        handle_error(data, ENOEXEC, "Invalid map.\tNo map found.");
    return (0);
}

int	parse_line(t_data *data, char *line)
{
    char *start;

    start = line_start(line);
    if (ft_strncmp(start, "NO", 2) == 0)
        return(parse_texture(data, start, 0));
    else if (ft_strncmp(start, "SO", 2) == 0)
        return(parse_texture(data, start, 1));
    else if (ft_strncmp(start, "WE", 2) == 0)
        return(parse_texture(data, start, 2));
    else if (ft_strncmp(start, "EA", 2) == 0)
        return(parse_texture(data, start, 3));
    else if (ft_strncmp(start, "F", 1) == 0)
        return(parse_color(data, start, 0));
    else if (ft_strncmp(start, "C", 1) == 0)
        return(parse_color(data, start, 1));
    else if (ft_strncmp(start, "1", 1) == 0)
        return(parse_map(data, line));
    else if (*start != '\0' && *start != '\n')
        handle_error(data, ENOEXEC, "Invalid map.");
    return (0);
}

int	parse_texture(t_data *data, char *line, int i)
{
    char *tmp;

    if (data->wall_textures[i])
        handle_error(data, ENOEXEC, "Invalid texture.\tMultiple textures found.");
    tmp = ft_strtrim(line + 2, " \n\t\v\f\r");
    data->wall_textures[i] = ft_strdup(tmp);
    free(tmp);
    return (0);
}
