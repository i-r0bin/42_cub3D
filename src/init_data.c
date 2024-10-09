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
    data->floor_color = 0;
    data->ceiling_color = 0;
}

void	init_mlx(t_data *data)
{
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->img_width, data->img_height, "cub3D");
    data->img = mlx_new_image(data->mlx_ptr, data->img_width, data->img_height);
    data->img_addr = (int *)mlx_get_data_addr(data->img, &data->bpp, &data->size_l, &data->endian);
}

void	init_textures(t_data *data)
{
    int i;

    data->wall_textures = ft_calloc(5, sizeof(char *));
    i = 0;
    while (i < 5)
    {
        data->wall_textures[i] = NULL;
        i++;
    }
}
