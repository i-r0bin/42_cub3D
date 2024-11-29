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

void	cub_free(t_data *data)
{
	free_texture(&data->north_texture);
	free_texture(&data->south_texture);
	free_texture(&data->west_texture);
	free_texture(&data->east_texture);
	if (data->map.map)
		free_matrix(data->map.map);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img);
	if (data->mlx.win_ptr)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	if (data->mlx.mlx_ptr)
	{
		mlx_destroy_display(data->mlx.mlx_ptr);
		free(data->mlx.mlx_ptr);
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	free_texture(t_texture *texture)
{
	int	i;

	i = 0;
	if (texture->path)
		free(texture->path);
	if (texture->color_table)
	{
		while (i < texture->colors_num)
			free(texture->color_table[i++].symbol);
		free(texture->color_table);
	}
	if (texture->color_matrix)
	{
		i = 0;
		while (texture->color_matrix[i])
			free(texture->color_matrix[i++]);
		free(texture->color_matrix);
	}
}
