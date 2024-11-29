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

void	render_column(t_data *data, t_raycast *raycast, int w, int x)
{
	int	y;

	y = raycast->drawStart;
	while (y < raycast->drawEnd)
	{
		raycast->texY = (int)raycast->texPos & (TEXTURE_SIZE - 1);
		raycast->texPos += raycast->step;
		raycast->texNum = get_tex_num(raycast->side, raycast->ray_x,
				raycast->ray_y);
		raycast->color = get_color_from_texture(data, raycast->texNum,
				raycast->texX, raycast->texY);
		if (raycast->side == 1)
			raycast->color = (raycast->color >> 1) & 0x7F7F7F;
		data->mlx.img_addr[y * w + x] = raycast->color;
		y++;
	}
}

int	get_tex_num(int side, double ray_x, double ray_y)
{
	if (side == 1 && ray_y < 0)
		return (0);
	else if (side == 1 && ray_y > 0)
		return (1);
	else if (side == 0 && ray_x < 0)
		return (2);
	else
		return (3);
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
