/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:14:19 by ppezzull          #+#    #+#             */
/*   Updated: 2024/11/27 20:14:21 by ppezzull         ###   ########.fr       */
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
