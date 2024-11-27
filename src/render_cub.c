/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:00:35 by ppezzull          #+#    #+#             */
/*   Updated: 2024/11/27 03:00:38 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" // Include necessary headers and declarations

void	init_raycast(t_raycast *raycast, t_data *data, int x, int w)
{
	raycast->cameraX = 2 * x / (double)w - 1;
	raycast->rayDirX = data->player.dir_x + data->player.plane_x
		* raycast->cameraX;
	raycast->rayDirY = data->player.dir_y + data->player.plane_y
		* raycast->cameraX;
	raycast->mapX = (int)data->player.x;
	raycast->mapY = (int)data->player.y;
	raycast->deltaDistX = fabs(1 / raycast->rayDirX);
	raycast->deltaDistY = fabs(1 / raycast->rayDirY);
	raycast->hit = 0;
}

void	calculate_step_and_side(t_raycast *raycast, t_data *data)
{
	if (raycast->rayDirX < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (data->player.x - raycast->mapX)
			* raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->mapX + 1.0 - data->player.x)
			* raycast->deltaDistX;
	}
	if (raycast->rayDirY < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (data->player.y - raycast->mapY)
			* raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->mapY + 1.0 - data->player.y)
			* raycast->deltaDistY;
	}
}

void	perform_dda(t_raycast *raycast, t_data *data)
{
	while (!raycast->hit)
	{
		if (raycast->sideDistX < raycast->sideDistY)
		{
			raycast->sideDistX += raycast->deltaDistX;
			raycast->mapX += raycast->stepX;
			raycast->side = 0;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player.y) * deltaDistY;
		}
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map.map[mapY][mapX] == '1')
				hit = 1;
		}
	}
}

void	render_wall_columns(t_data *data, int w, int h)
{
	int			x;
	t_raycast	raycast;

	x = 0;
	while (x < w)
	{
		init_raycast(&raycast, data, x, w);
		calculate_step_and_side(&raycast, data);
		perform_dda(&raycast, data);
		calculate_wall_params(&raycast, data, h);
		if (raycast.side == 0)
		{
			raycast.wallX = data->player.y + raycast.perpWallDist
				* raycast.rayDirY;
		}
		else
		{
			raycast.wallX = data->player.x + raycast.perpWallDist
				* raycast.rayDirX;
		}
		calculate_texture_params(&raycast, h);
		render_column(data, &raycast, w, x);
		x++;
	}
}

void	render_cub(t_data *data)
{
	int	w;
	int	h;

	w = data->mlx.img_width;
	h = data->mlx.img_height;
	fill_ceiling_and_floor(data, w, h);
	render_wall_columns(data, w, h);
}
