/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:59:38 by ppezzull          #+#    #+#             */
/*   Updated: 2024/11/30 21:27:37 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_data *data, int mapsize)
{
	int	x;
	int	y;

	draw_map_background(data, mapsize, 0xADD8E6);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.map[y][x] != '\0')
		{
			if (data->map.map[y][x] == '1')
			{
				draw_square(data, x, y, mapsize, 0x000040);
			}
			x++;
		}
		y++;
	}
	draw_player(data, mapsize, 0xFF0000);
}

void	draw_square(t_data *data, int x, int y, int mapsize, unsigned int color)
{
	int	i;
	int	j;

	x = x * mapsize + mapsize;
	y = y * mapsize + mapsize;
	i = 0;
	while (i < mapsize)
	{
		j = 0;
		while (j < mapsize)
		{
			if (x + j > data->mlx.img_width || y + i > data->mlx.img_height
				|| x < 0 || y < 0)
				break ;
			data->mlx.img_addr[(y + i) * data->mlx.img_width + (x + j)] = color;
			j++;
		}
		i++;
	}
}

void draw_player(t_data *data, int mapsize, unsigned int color)
{
	int x_center;
	int y_center;
	int radius;

	x_center = data->player.x * (double)mapsize + mapsize;
	y_center = data->player.y * (double)mapsize + mapsize;
	radius = mapsize / 4;
	draw_circle(data, x_center, y_center, radius, color);
}

void draw_circle(t_data *data, int x_center, int y_center, int radius, unsigned int color)
{
	int x;
	int y;

	x = -radius;
	while (x <= radius)
	{
		y = -radius;
		while (y <= radius)
		{
			if (x_center + x >= 0 && x_center + x < data->mlx.img_width &&
				y_center + y >= 0 && y_center + y < data->mlx.img_height &&
				x * x + y * y <= radius * radius)
			{
				data->mlx.img_addr[(y_center + y) * data->mlx.img_width + (x_center + x)] = color;
			}
			y++;
		}
		x++;
	}
}

void	draw_map_background(t_data *data, int mapsize, unsigned int color)
{
	int x;
	int y;

	y = mapsize - mapsize / 3;
	while (y < data->map.height * mapsize + mapsize + mapsize / 3)
	{
		x = mapsize - mapsize / 3;
		while (x < data->map.width * mapsize + mapsize + mapsize / 3)
		{
			if (x >= 0 && x < data->mlx.img_width && y >= 0 && y < data->mlx.img_height)
			{
				data->mlx.img_addr[y * data->mlx.img_width + x] = color;
			}
			x++;
		}
		y++;
	}
}
