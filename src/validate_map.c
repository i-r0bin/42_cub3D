/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:57:03 by ppezzull          #+#    #+#             */
/*   Updated: 2024/12/06 22:57:37 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(t_data *data)
{
	if (data->map.map == NULL)
		handle_error(data, ENOEXEC, "Invalid map.\tMap is missing.");
	if (data->pov == '0')
		handle_error(data, ENOEXEC,
			"Invalid map.\tPlayer position is missing.");
	if (check_map_characters(&data->map) == 1)
		handle_error(data, ENOEXEC, "Invalid map.\tInvalid character found.");
	if (check_map_borders(&data->map) == 1)
		handle_error(data, ENOEXEC, "Invalid map.\tMap is not closed.");
	return (0);
}

int	check_map_characters(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map && map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_borders(t_map *map)
{
	int	i;

	i = 0;
	while (map && map->map[i] != NULL)
	{
		if (check_map_row_borders(map, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_map_row_borders(t_map *map, int i)
{
	int	j;

	j = 0;
	while (map->map[i][j] != '\0')
	{
		if (map->map[i][j] == '0')
		{
			if (i > 0 && (j >= (int)ft_strlen(map->map[i - 1])
					|| map->map[i - 1][j] == ' '))
				return (1);
			if (i < map->height - 1 && (j >= (int)ft_strlen(map->map[i + 1])
					|| map->map[i + 1][j] == ' '))
				return (1);
			if (j > 0 && map->map[i][j - 1] == ' ')
				return (1);
			if (j < (int)ft_strlen(map->map[i]) - 1
				&& map->map[i][j + 1] == ' ')
				return (1);
		}
		j++;
	}
	return (0);
}
