/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:59:38 by ppezzull          #+#    #+#             */
/*   Updated: 2024/11/27 02:59:41 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_zoom(int *x, int *y, int zoom)
{
	*x *= zoom;
	*y *= zoom;
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.map[y][x] != '\0')
		{
			if (data->map.map[y][x] == '1')
				draw_borders(data, x, y);
			else if (data->map.map[y][x] == '0' || data->map.map[y][x] == 'N'
				|| data->map.map[y][x] == 'S' || data->map.map[y][x] == 'W'
				|| data->map.map[y][x] == 'E')
				draw_floor(data, x, y);
			x++;
		}
		y++;
	}
	draw_point(data, (int)data->player.x, (int)data->player.y);
}

void	draw_borders(t_data *data, int x, int y)
{
	int	i;
	int	j;

	set_zoom(&x, &y, data->minimap_size);
	i = 0;
	while (i < data->minimap_size)
	{
		j = 0;
		while (j < data->minimap_size)
		{
			if (!(x + j > data->mlx.img_width || y + i > data->mlx.img_height
					|| x < 0 || y < 0))
				data->mlx.img_addr[(y + i) * data->mlx.img_width + (x
						+ j)] = 0x404040;
			j++;
		}
		i++;
	}
}

void	draw_floor(t_data *data, int x, int y)
{
	int	i;
	int	j;

	set_zoom(&x, &y, data->minimap_size);
	i = 0;
	while (i < data->minimap_size)
	{
		j = 0;
		while (j < data->minimap_size)
		{
			if (x + j > data->mlx.img_width || y + i > data->mlx.img_height
				|| x < 0 || y < 0)
				break ;
			if (i == 0 || i == data->minimap_size - 1 || j == 0
				|| j == data->minimap_size - 1)
				data->mlx.img_addr[(y + i) * data->mlx.img_width + (x
						+ j)] = 0x000000;
			else
				data->mlx.img_addr[(y + i) * data->mlx.img_width + (x
						+ j)] = 0xffffff;
			j++;
		}
		i++;
	}
}

void	draw_point(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	radius;
	int	dx;
	int	dy;

	set_zoom(&x, &y, data->minimap_size);
	i = -1;
	while (++i < data->minimap_size)
	{
		j = 0;
		while (j < data->minimap_size)
		{
			if (x + j > data->mlx.img_width || y + i > data->mlx.img_height
				|| x < 0 || y < 0)
				break ;
			radius = data->minimap_size / 4;
			dx = j - data->minimap_size / 2;
			dy = i - data->minimap_size / 2;
			if (dx * dx + dy * dy <= radius * radius)
				data->mlx.img_addr[(y + i) * data->mlx.img_width + (x
						+ j)] = 0xff0000;
			j++;
		}
	}
}
