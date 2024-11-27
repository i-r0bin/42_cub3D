/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:00:20 by ppezzull          #+#    #+#             */
/*   Updated: 2024/11/27 03:00:23 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_map(t_data *data, char *line)
{
	int		i;
	char	**new_map;

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
}

void	set_player_position(t_data *data, char *line, int i)
{
	int	j;

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
	if (j > data->map.width)
	{
		data->map.width = j;
	}
}

int	parse_map(t_data *data, char *line)
{
	check_elements(data);
	update_map(data, line);
	set_player_position(data, line, data->map.height - 1);
	return (0);
}
