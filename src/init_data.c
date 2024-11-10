#include "cub3d.h"

void	init_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img = NULL;
	data->img_addr = NULL;
	data->img_width = 1500;
	data->img_height = 800;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = '0';
	data->player_speed = 0;
	data->player_rot_speed = 0;
	init_textures(data);
	data->floor_color = -1;
	data->ceiling_color = -1;

    data->dir_x = 1.0;   // Example value, adjust as needed
    data->dir_y = 0.0;

    // Set the camera plane for a field of view of 66 degrees:
    data->plane_x = 0.0;
    data->plane_y = 0.66; // Adjust as needed for horizontal or vertical FOV
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		handle_error(data, EIO, "Failed to initialize mlx.");
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img_width,
			data->img_height, "cub3D");
	if (data->win_ptr == NULL)
		handle_error(data, EIO, "Failed to create window.");
	data->img = mlx_new_image(data->mlx_ptr, data->img_width, data->img_height);
	if (data->img == NULL)
		handle_error(data, EIO, "Failed to create image.");
}

void	init_textures(t_data *data)
{
	int	i;

	data->wall_textures = ft_calloc(4, sizeof(char *));
	i = 0;
	while (i < 4)
	{
		data->wall_textures[i] = NULL;
		i++;
	}
}

int	set_image(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, data->img_width, data->img_height);
	data->img_addr = (int *)mlx_get_data_addr(data->img, &data->bpp,
			&data->size_l, &data->endian);
	if (data->img_addr == NULL)
		handle_error(data, EIO, "Failed to get image address.");
	return (0);
}