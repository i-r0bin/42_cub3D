#include "cub3d.h"

void	print_controls(void)
{
	ft_putendl_fd("Controls:", 1);
	ft_putendl_fd("Move forward: W", 1);
	ft_putendl_fd("Move backward: S", 1);
	ft_putendl_fd("Strafe left: A", 1);
	ft_putendl_fd("Strafe right: D", 1);
	ft_putendl_fd("Look left: Left arrow", 1);
	ft_putendl_fd("Look right: Right arrow", 1);
	ft_putendl_fd("Exit: ESC", 1);
}

void	listen_for_input(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, cub_exit, data);
	mlx_hook(data->win_ptr, ConfigureNotify, StructureNotifyMask, resize_window,
		data);
}

int	render(t_data *data)
{
	set_image(data);
	render_cub(data);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (argc == 1)
		handle_error(&data, EINVAL,
			"Missing argument. Try:\t./cub3D path/to/map.cub");
	else if (argc > 2)
		handle_error(&data, EINVAL,
			"Too many arguments. Try:\t./cub3D path/to/map.cub");
	parse_args(&data, argv);
	init_mlx(&data);
	print_controls();
	listen_for_input(&data);
	mlx_loop_hook(data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
