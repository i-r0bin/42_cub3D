/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:51:32 by ppezzull          #+#    #+#             */
/*   Updated: 2024/11/27 16:51:34 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_params(t_raycast *raycast, t_data *data, int h)
{
	if (raycast->side == 0)
	{
		raycast->perpWallDist = (raycast->mapX - data->player.x + (1
					- raycast->stepX) / 2) / raycast->rayDirX;
	}
	else
	{
		raycast->perpWallDist = (raycast->mapY - data->player.y + (1
					- raycast->stepY) / 2) / raycast->rayDirY;
	}
	raycast->lineHeight = (int)(h / raycast->perpWallDist);
	raycast->drawStart = -raycast->lineHeight / 2 + h / 2;
	raycast->drawEnd = raycast->lineHeight / 2 + h / 2;
	if (raycast->drawStart < 0)
		raycast->drawStart = 0;
	if (raycast->drawEnd >= h)
		raycast->drawEnd = h - 1;
}

void	fill_ceiling_and_floor(t_data *data, int w, int h)
{
	int	y;
	int	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (y < h / 2)
				data->mlx.img_addr[y * w + x] = data->ceiling_color;
			else
				data->mlx.img_addr[y * w + x] = data->floor_color;
			x++;
		}
		y++;
	}
}

void	calculate_texture_params(t_raycast *raycast, int h)
{
	raycast->wallX -= floor(raycast->wallX);
	raycast->texX = (int)(raycast->wallX * (double)TEXTURE_SIZE);
	if (raycast->side == 0 && raycast->rayDirX > 0)
		raycast->texX = TEXTURE_SIZE - raycast->texX - 1;
	if (raycast->side == 1 && raycast->rayDirY < 0)
		raycast->texX = TEXTURE_SIZE - raycast->texX - 1;
	raycast->step = 1.0 * TEXTURE_SIZE / raycast->lineHeight;
	raycast->texPos = (raycast->drawStart - h / 2 + raycast->lineHeight / 2)
		* raycast->step;
}

void	render_column(t_data *data, t_raycast *raycast, int w, int x)
{
	int	y;

	y = raycast->drawStart;
	while (y < raycast->drawEnd)
	{
		raycast->texY = (int)raycast->texPos & (TEXTURE_SIZE - 1);
		raycast->texPos += raycast->step;
		raycast->texNum = data->map.map[raycast->mapY][raycast->mapX] - '1';
		raycast->color = get_color_from_texture(data, raycast->texNum,
				raycast->texX, raycast->texY);
		if (raycast->side == 1)
			raycast->color = (raycast->color >> 1) & 0x7F7F7F;
		data->mlx.img_addr[y * w + x] = raycast->color;
		y++;
	}
}

unsigned int	get_color_from_texture(t_data *data, int texNum, int texX,
		int texY)
{
	unsigned int	color;

	if (texNum == 0)
		color = data->north_texture.color_matrix[texY][texX];
	else if (texNum == 1)
		color = data->south_texture.color_matrix[texY][texX];
	else if (texNum == 2)
		color = data->west_texture.color_matrix[texY][texX];
	else if (texNum == 3)
		color = data->east_texture.color_matrix[texY][texX];
	else
		color = 0x00FF00;
	return (color);
}
