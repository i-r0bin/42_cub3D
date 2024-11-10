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
		data->img_width = xce.width;
		data->img_height = xce.height;
	}
	return (0);
}

void	move_player(t_data *data, char dir)
{
	if (dir == 'W' && data->map[data->player_y - 1][data->player_x] != '1')
		data->player_y -= 1;
	else if (dir == 'S' && data->map[data->player_y + 1][data->player_x] != '1')
		data->player_y += 1;
	else if (dir == 'A' && data->map[data->player_y][data->player_x - 1] != '1')
		data->player_x -= 1;
	else if (dir == 'D' && data->map[data->player_y][data->player_x + 1] != '1')
		data->player_x += 1;
	draw_map(data);
	render_cub(data);
}

void	rotate_player(t_data *data, int dir)
{
	data = data;
	dir = dir;
	return ;
}