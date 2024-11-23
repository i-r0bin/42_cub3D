#include "cub3d.h"

int	parse_map(t_data *data, char *line)
{
	int		i;
	int		j;
	char	**new_map;

	check_elements(data);
	i = 0;
	while (data->map.map && data->map.map[i] != NULL)
		i++;
	new_map = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (data->map.map && data->map.map[i] != NULL)
	{
		new_map[i] = ft_strdup(data->map.map[i]);
		free(data->map.map[i]);
		i++;
	}
	new_map[i] = ft_strdup(line);
	if (data->map.map)
		free(data->map.map);
	data->map.map = new_map;
	data->map.height++;
	j = 0;
	while (line[j] != '\0' && line[j] != '\n')
	{
		if (line[j] == 'W' || line[j] == 'E' || line[j] == 'N'
			|| line[j] == 'S')
		{
			if (data->starting_dir != '0')
				handle_error(data, ENOEXEC,
						"Invalid map.\tMultiple player positions found.");
			data->player.x = j;
			data->player.y = i;
			data->starting_dir = line[j];
		}
		j++;
	}
	data->map.width = (j > data->map.width) ? j : data->map.width;
	return (0);
}
