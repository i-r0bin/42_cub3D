/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:00:43 by ppezzull          #+#    #+#             */
/*   Updated: 2024/11/27 03:00:46 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*line_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (line + i);
}

int	is_texture(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		return (1);
	return (0);
}

int	cub_exit(t_data *data)
{
	cub_free(data);
	exit(0);
}

int	resize_window(t_data *data, XEvent *event)
{
	XConfigureEvent	xce;

	if (event->type == ConfigureNotify)
	{
		xce = event->xconfigure;
		data->mlx.img_width = xce.width;
		data->mlx.img_height = xce.height;
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
