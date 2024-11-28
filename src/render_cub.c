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

void	calculate_step_and_side(t_raycast *raycast, t_data *data)
{
	if (raycast->ray_x < 0)
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
	if (raycast->ray_y < 0)
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

void	step_and_update_side_dist(t_raycast *raycast)
{
	if (raycast->sideDistX < raycast->sideDistY)
	{
		raycast->sideDistX += raycast->deltaDistX;
		raycast->mapX += raycast->stepX;
		raycast->side = 0;
	}
	else
	{
		raycast->sideDistY += raycast->deltaDistY;
		raycast->mapY += raycast->stepY;
		raycast->side = 1;
	}
}

void	perform_dda(t_raycast *raycast, t_data *data)
{
	while (!raycast->hit)
	{
		step_and_update_side_dist(raycast);
		if (data->map.map[raycast->mapY][raycast->mapX] == '1')
			raycast->hit = 1;
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
				* raycast.ray_y;
		}
		else
		{
			raycast.wallX = data->player.x + raycast.perpWallDist
				* raycast.ray_x;
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
