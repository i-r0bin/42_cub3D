#include "cub3d.h"

void	listen_for_input(t_data *data)
{
    mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press, data);
    mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, cub_exit, data);
    mlx_hook(data->win_ptr, ConfigureNotify, StructureNotifyMask, resize_window, data);
}

int	set_image(t_data *data)
{
    if (data->img)
        mlx_destroy_image(data->mlx_ptr, data->img);
    data->img = mlx_new_image(data->mlx_ptr, data->img_width, data->img_height);
    data->img_addr = (int *)mlx_get_data_addr(data->img, &data->bpp, &data->size_l, &data->endian);
	if (data->img_addr == NULL)
		cub_exit(data);
	return (0);
}

int render(t_data *data)
{
    set_image(data);
    //render_cub(data);
    draw_map(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
    return (0);
}

int	main(int argc, char **argv)
{
    t_data data;
    int err;

	if (argc != 2)
		return (err_msg("Usage:\t./cub3D <map.cub>\nError", EINVAL));
    init_data(&data);
    err = parse_args(&data, argv);
	if (err != 0)
    {
        cub_free(&data);
        return (err);
    }
	init_mlx(&data);
    print_controls();
    listen_for_input(&data);
    mlx_loop_hook(data.mlx_ptr, render, &data);
    render(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
