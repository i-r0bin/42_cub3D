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

int	parse_map(t_data *data, char *line, int fd)
{
	int	endmap;

	endmap = 0;
	while (line && *line != '\0')
	{
		if (endmap == 0)
			endmap = parse_map_line(data, line);
		else if (*line_start(line) != '\0' && *line_start(line) != '\n')
			handle_error(data, ENOEXEC, "Invalid map.");
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_map_line(t_data *data, char *line)
{
	int		i;
	int		len;
	char	**new_map;

	len = get_row_len(line);
	if (len == 0)
		return (1);
	new_map = ft_calloc(data->map.height + 2, sizeof(char *));
	i = 0;
	while (data->map.map && data->map.map[i] != NULL)
	{
		new_map[i] = ft_strdup(data->map.map[i]);
		i++;
	}
	new_map[i] = ft_calloc(len + 1, sizeof(char));
	if (new_map[i] == NULL)
		handle_error(data, ENOMEM, "Memory allocation failed.");
	ft_strlcpy(new_map[i], line, len + 1);
	new_map[i + 1] = NULL;
	if (data->map.map)
		free_matrix(data->map.map);
	data->map.map = new_map;
	data->map.height++;
	if ((int)ft_strlen(new_map[i]) > data->map.width)
		data->map.width = (int)ft_strlen(new_map[i]);
	update_player_position(data);
	return (0);
}

int	update_player_position(t_data *data)
{
	int	i;
	int	j;

	i = data->map.height - 1;
	j = 0;
	while (data->map.map[i][j])
	{
		if (data->map.map[i][j] == 'W' || data->map.map[i][j] == 'E'
			|| data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S')
		{
			if (data->pov != '0')
				handle_error(data, ENOEXEC,
						"Invalid map.\tMultiple player positions found.");
			data->player.x = j + 0.5;
			data->player.y = i + 0.5;
			data->pov = data->map.map[i][j];
			data->map.map[i][j] = '0';
		}
		j++;
	}
	return (0);
}
int	get_row_len(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i == 0)
		return (0);
	while (str[i] == ' ' || str[i] == '\n')
		i--;
	return (i + 1);
}
