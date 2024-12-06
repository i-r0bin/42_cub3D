/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:10:40 by rilliano          #+#    #+#             */
/*   Updated: 2024/12/06 22:10:42 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	format_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		fill_with_zeros(map->map[i]);
		i++;
	}
	i = 0;
	while (i < map->width)
	{
		remove_extra_zeros(map, i);
		i++;
	}
}

void	fill_with_zeros(char *line)
{
	int		j;
	char	*start;

	start = line_start(line);
	j = 0;
	while (start[j] != '\0')
	{
		if (start[j] == ' ')
			start[j] = '0';
		j++;
	}
}

void	remove_extra_zeros(t_map *map, int i)
{
	int	j;

	j = 0;
	while (j < map->height && (i >= (int)ft_strlen(map->map[j])
			|| map->map[j][i] == '0' || map->map[j][i] == ' '))
	{
		if (map->map[j][i] == '0')
			map->map[j][i] = ' ';
		j++;
	}
	if (j != map->height && j != map->height - 1)
	{
		j = map->height - 1;
		while (j >= 0 && (i >= (int)ft_strlen(map->map[j])
				|| map->map[j][i] == '0' || map->map[j][i] == ' '))
		{
			if (map->map[j][i] == '0')
				map->map[j][i] = ' ';
			j--;
		}
	}
}
