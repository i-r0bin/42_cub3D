/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:59:54 by ppezzull          #+#    #+#             */
/*   Updated: 2024/11/27 02:59:59 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_w)
		move_player(data, 'W');
	else if (keycode == XK_s)
		move_player(data, 'S');
	else if (keycode == XK_a)
		move_player(data, 'A');
	else if (keycode == XK_d)
		move_player(data, 'D');
	else if (keycode == XK_Left)
		rotate_player(data, -1);
	else if (keycode == XK_Right)
		rotate_player(data, 1);
	else if (keycode == XK_Escape)
		cub_exit(data);
	return (0);
}

int	cub_exit(t_data *data)
{
	cub_free(data);
	exit(0);
}

int	resize_window(t_data *data, XEvent *event)
{
	XConfigureEvent	xce;

	if (event->type == ConfigureNotify)
	{
		xce = event->xconfigure;
		data->mlx.img_width = xce.width;
		data->mlx.img_height = xce.height;
	}
	return (0);
}

void	move_player(t_data *data, char dir)
{
	if (dir == 'W' && data->map.map[data->player.y - 1][data->player.x] != '1')
		data->player.y -= 1;
	else if (dir == 'S' && data->map.map[data->player.y
			+ 1][data->player.x] != '1')
		data->player.y += 1;
	else if (dir == 'A' && data->map.map[data->player.y][data->player.x
		- 1] != '1')
		data->player.x -= 1;
	else if (dir == 'D' && data->map.map[data->player.y][data->player.x
		+ 1] != '1')
		data->player.x += 1;
}

void	rotate_player(t_data *data, int dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotate_angle;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	rotate_angle = dir * ROTATE_SPEED;
	data->player.dir_x = data->player.dir_x * cos(rotate_angle)
		- data->player.dir_y * sin(rotate_angle);
	data->player.dir_y = old_dir_x * sin(rotate_angle) + data->player.dir_y
		* cos(rotate_angle);
	data->player.plane_x = data->player.plane_x * cos(rotate_angle)
		- data->player.plane_y * sin(rotate_angle);
	data->player.plane_y = old_plane_x * sin(rotate_angle)
		+ data->player.plane_y * cos(rotate_angle);
	render_cub(data);
}
