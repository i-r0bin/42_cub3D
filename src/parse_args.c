#include "cub3d.h"

int	parse_args(t_data *data, char **av)
{
	int		fd;
	char	*format;

	format = ft_strrchr(av[1], '.');
	if (!format || ft_strlen(format) != 4 || ft_strncmp(ft_strrchr(av[1], '.'),
			".cub", 4) != 0)
		handle_error(data, EINVAL,
				"Invalid file format. Only .cub files are accepted.");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		handle_error(data, errno, "Failed to open file.");
	parse_file(data, fd);
	close(fd);
	parse_textures(data);
	return (0);
}

int	parse_file(t_data *data, int fd)
{
	char	*line;
	int		end_map;

	end_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line_start(line) == '\n' && data->map.map)
			end_map = 1;
		else if (*line_start(line) == '1' && end_map == 1)
			handle_error(data, ENOEXEC, "Invalid map.");
		parse_line(data, line);
		free(line);
		line = get_next_line(fd);
	}
	if (!data->map.map)
		handle_error(data, ENOEXEC, "Invalid map.\tNo map found.");
	return (0);
}

int	parse_line(t_data *data, char *line)
{
	char	*start;

	start = line_start(line);
	if (is_texture(start))
		return (save_texture_path(data, start));
	else if (ft_strncmp(start, "F", 1) == 0)
		return (parse_color(data, start, 0));
	else if (ft_strncmp(start, "C", 1) == 0)
		return (parse_color(data, start, 1));
	else if (ft_strncmp(start, "1", 1) == 0)
		return (parse_map(data, line));
	else if (*start != '\0' && *start != '\n')
		handle_error(data, ENOEXEC, "Invalid map.");
	return (0);
}

int	save_texture_path(t_data *data, char *line)
{
	char	*tmp;
	char	k;

	k = *line;
	tmp = ft_strtrim(line + 2, " \n\t\v\f\r");
	if (!tmp)
		handle_error(data, ENOMEM, "Failed to allocate memory.");
	if (k == 'N' && data->north_texture.path == NULL)
		data->north_texture.path = ft_strdup(tmp);
	else if (k == 'S' && data->south_texture.path == NULL)
		data->south_texture.path = ft_strdup(tmp);
	else if (k == 'W' && data->west_texture.path == NULL)
		data->west_texture.path = ft_strdup(tmp);
	else if (k == 'E' && data->east_texture.path == NULL)
		data->east_texture.path = ft_strdup(tmp);
	else
		handle_error(data, ENOEXEC,
				"Invalid texture.\tMultiple textures found.");
	free(tmp);
	return (0);
}

int	parse_color(t_data *data, char *line, int i)
{
	int	rgb;

	if (i == 0 && data->floor_color != -1)
		handle_error(data, ENOEXEC,
				"Invalid color.\tMultiple floor colors found.");
	else if (i == 1 && data->ceiling_color != -1)
		handle_error(data, ENOEXEC,
				"Invalid color.\tMultiple ceiling colors found.");
	rgb = get_color_from_rgb_str(line + 1);
	if (rgb == -1)
		handle_error(data, ENOEXEC, "Invalid color.");
	if (i == 0)
		data->floor_color = rgb;
	else
		data->ceiling_color = rgb;
	return (0);
}
