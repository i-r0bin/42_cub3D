#include "cub3d.h"

void	set_zoom(int *x, int *y)
{
    *x *= MAP_SIZE;
    *y *= MAP_SIZE;
}

void	set_param(int *x, int *y, t_data *data)
{
    set_zoom(x, y);
    *x += data->img_width - data->map_width * MAP_SIZE - 10;
    *y += data->img_height - data->map_height * MAP_SIZE - 10;
}

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

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	cub_free(t_data *data)
{
    if (data->wall_textures)
        free_matrix(data->wall_textures);
    if (data->map)
        free_matrix(data->map);
    if (data->img)
        mlx_destroy_image(data->mlx_ptr, data->img);
    if (data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (data->mlx_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
    }
}
