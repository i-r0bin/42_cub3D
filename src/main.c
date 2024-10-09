#include "cub3d.h"

void	listen_for_input(t_data *data)
{
    mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data); //mlx_hook is a function that binds a key press event to a function. Here, the parameters are the window pointer, the event code, the event mask, and the function to call. The event mask is a bitmask that specifies which events to listen for. In this case 1L << 0 represents
    mlx_hook(data->win_ptr, 17, 1L << 17, close_win, data);
}

int	main(int argc, char **argv)
{
    t_data data;

	if (argc != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
	init_data(&data);
	if (parse_args(&data, argv) != 0)
    {
        cub_free(&data);
        return (1);
    }
	init_mlx(&data);
    print_controls();
    listen_for_input(&data);
    //render_images(&data);
    draw_map(&data);
    //mlx_loop_hook(data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

int get_wall_color(t_data *data, int x, int y, int i, int j)
{
    int color;
    int texture;
    int tex_x;
    int tex_y;

    texture = data->map[y][x] - '1';
    tex_x = (int)(i * TEXTURE_SIZE / TILE_SIZE);
    tex_y = (int)(j * TEXTURE_SIZE / TILE_SIZE);
    color = get_texture_color(data, data->wall_textures[texture], tex_x, tex_y);
    return (color);
}

int	get_texture_color(t_data *data, char *texture, int x, int y)
{
    int color;
    int i;

    i = 0;
    while (i < TEXTURE_SIZE)
    {
        color = get_pixel_color(data, texture, x, y);
        if (color != 0x000000)
            return (color);
        i++;
    }
    return (0x000000);
}

int	get_pixel_color(t_data *data, char *texture, int x, int y)
{
    int color;
    int i;

    i = 0;
    while (i < data->img_width * data->img_height)
    {
        color = get_color(data, texture, x, y);
        if (color != 0x000000)
            return (color);
        i++;
    }
    return (0x000000);
}

int	get_color(t_data *data, char *texture, int x, int y)
{
    int color;
    int i;

    i = 0;
    texture = texture;
    while (i < data->img_width * data->img_height)
    {
        color = data->img_addr[y * data->img_width + x];
        if (color != 0x000000)
            return (color);
        i++;
    }
    return (0x000000);
}
