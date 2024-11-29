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

void	init_raycast(t_raycast *raycast, t_data *data, int x, int w)
{
	raycast->camera_x = 2 * x / (double)w - 1;
	raycast->ray_x = data->player.dir_x + data->player.plane_x
		* raycast->camera_x;
	raycast->ray_y = data->player.dir_y + data->player.plane_y
		* raycast->camera_x;
	raycast->mapX = (int)data->player.x;
	raycast->mapY = (int)data->player.y;
	raycast->deltaDistX = fabs(1 / raycast->ray_x);
	raycast->deltaDistY = fabs(1 / raycast->ray_y);
	raycast->hit = 0;
}

void	calculate_wall_params(t_raycast *raycast, t_data *data, int h)
{
	if (raycast->side == 0)
	{
		raycast->perpWallDist = (raycast->mapX - data->player.x + (1
					- raycast->stepX) / 2) / raycast->ray_x;
	}
	else
	{
		raycast->perpWallDist = (raycast->mapY - data->player.y + (1
					- raycast->stepY) / 2) / raycast->ray_y;
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
	if (raycast->side == 0 && raycast->ray_x > 0)
		raycast->texX = TEXTURE_SIZE - raycast->texX - 1;
	if (raycast->side == 1 && raycast->ray_y < 0)
		raycast->texX = TEXTURE_SIZE - raycast->texX - 1;
	raycast->step = 1.0 * TEXTURE_SIZE / raycast->lineHeight;
	raycast->texPos = (raycast->drawStart - h / 2 + raycast->lineHeight / 2)
		* raycast->step;
}
