#include "cub3d.h"

int	parse_map(t_data *data, char *line)
{
    int i;
    int j;
    char **new_map;

    i = 0;
    while (data->map && data->map[i] != NULL)
        i++;
    new_map = ft_calloc(i + 2, sizeof(char *));
    i = 0;
    while (data->map && data->map[i] != NULL)
    {
        new_map[i] = ft_strdup(data->map[i]);
        free(data->map[i]);
        i++;
    }
    new_map[i] = ft_strdup(line);
    if (data->map)
        free(data->map);
    data->map = new_map;
    data->map_height++;
    j = 0;
    while (line[j] != '\0' && line[j] != '\n')
    {
        if (line[j] == 'W' || line[j] == 'E' || line[j] == 'N' || line[j] == 'S')
        {
            if (data->player_dir != '0')
                return (err_msg("Invalid map\nError", ENOEXEC));
            data->player_x = j;
            data->player_y = i;
            data->player_dir = line[j];
        }
        j++;
    }
    data->map_width = (j > data->map_width) ? j : data->map_width;
    return (0);
}
