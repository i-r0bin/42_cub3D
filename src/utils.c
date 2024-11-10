#include "cub3d.h"

void	set_zoom(int *x, int *y)
{
	*x *= MAP_SIZE;
	*y *= MAP_SIZE;
}

char	*line_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (line + i);
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
