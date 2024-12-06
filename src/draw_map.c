/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:59:38 by ppezzull          #+#    #+#             */
/*   Updated: 2024/12/06 22:45:50 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_data *data)
{
	int			x;
	int			y;
	t_minimap	minimap;

	init_minimap(data, &minimap);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.map[y][x] != '\0')
		{
			if (data->map.map[y][x] == '1')
				draw_square(data, x, y, &minimap);
			else if (data->map.map[y][x] == '0')
				draw_square(data, x, y, &minimap);
			x++;
		}
		y++;
	}
	draw_player(data, &minimap);
}

void	init_minimap(t_data *data, t_minimap *minimap)
{
	minimap->size = 15;
	minimap->background_color = 0xADD8E6;
	minimap->wall_color = 0x000040;
	minimap->player_color = 0xFF0000;
	minimap->x_center = data->player.x * (double)minimap->size + minimap->size;
	minimap->y_center = data->player.y * (double)minimap->size + minimap->size;
	minimap->radius = minimap->size / 4;
}

unsigned int	get_minimap_color(t_minimap *minimap, char el)
{
	if (el == '1')
		return (minimap->wall_color);
	else if (el == '0')
		return (minimap->background_color);
	else
		return (0);
}

void	draw_square(t_data *data, int x, int y, t_minimap *minimap)
{
	int				i;
	int				j;
	unsigned int	color;

	color = get_minimap_color(minimap, data->map.map[y][x]);
	x = x * minimap->size + minimap->size;
	y = y * minimap->size + minimap->size;
	i = 0;
	while (i < minimap->size)
	{
		j = 0;
		while (j < minimap->size)
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

void	draw_player(t_data *data, t_minimap *minimap)
{
	int	x;
	int	y;

	x = -minimap->radius;
	while (x <= minimap->radius)
	{
		y = -minimap->radius;
		while (y <= minimap->radius)
		{
			if (minimap->x_center + x >= 0 && minimap->x_center
				+ x < data->mlx.img_width && minimap->y_center + y >= 0
				&& minimap->y_center + y < data->mlx.img_height && x * x + y
				* y <= minimap->radius * minimap->radius)
			{
				data->mlx.img_addr[(minimap->y_center + y) * data->mlx.img_width
					+ (minimap->x_center + x)] = minimap->player_color;
			}
			y++;
		}
		x++;
	}
}
