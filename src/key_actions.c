#include "cub3d.h"
#define ROTATE_SPEED 0.05

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
}
void rotate_player(t_data *data, int dir)
{
    double old_dir_x = data->dir_x;
    double old_plane_x = data->plane_x;
    double rotate_angle = dir * ROTATE_SPEED;

    // Rotate direction vector
    data->dir_x = data->dir_x * cos(rotate_angle) - data->dir_y * sin(rotate_angle);
    data->dir_y = old_dir_x * sin(rotate_angle) + data->dir_y * cos(rotate_angle);

    // Rotate camera plane
    data->plane_x = data->plane_x * cos(rotate_angle) - data->plane_y * sin(rotate_angle);
    data->plane_y = old_plane_x * sin(rotate_angle) + data->plane_y * cos(rotate_angle);

    printf("Player rotated %s\n", dir > 0 ? "right" : "left");
    render_cub(data);
}