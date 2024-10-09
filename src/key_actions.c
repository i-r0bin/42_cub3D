#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
    if (keycode == KEY_W)
        move_player(data, 'W');
    else if (keycode == KEY_S)
        move_player(data, 'S');
    else if (keycode == KEY_A)
        move_player(data, 'A');
    else if (keycode == KEY_D)
        move_player(data, 'D');
    else if (keycode == KEY_LEFT)
        rotate_player(data, -1);
    else if (keycode == KEY_RIGHT)
        rotate_player(data, 1);
    else if (keycode == KEY_ESC)
        close_win(data);
    return (0);
}

int	close_win(t_data *data)
{
	cub_free(data);
    exit(0);
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
}

void	rotate_player(t_data *data, int dir)
{
    data = data;
    dir = dir;
    return ;
}