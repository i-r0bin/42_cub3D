#include "cub3d.h"

char	**ft_strtrim_split(char **strs, char *set)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strs[i])
	{
		tmp = strs[i];
		strs[i] = ft_strtrim(strs[i], set);
		free(tmp);
		i++;
	}
	return (strs);
}

int	ft_isdigit_split(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i] && strs[i][0])
	{
		j = 0;
		while (strs[i][j])
		{
			if (!ft_isdigit(strs[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (i);
}

int	get_hex_color(char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

int	get_color(char *str)
{
	char	**rgb;
	int		color;

	rgb = ft_split(str, ',');
	ft_strtrim_split(rgb, " \n\t\v\f\r");
	if (ft_isdigit_split(rgb) != 3)
		return (-1);
	color = get_hex_color(rgb);
	free_matrix(rgb);
	return (color);
}

int	parse_color(t_data *data, char *line, int i)
{
	int	rgb;

	if (i == 0 && data->floor_color != -1)
		handle_error(data, ENOEXEC,
			"Invalid color.\tMultiple floor colors found.");
	else if (i == 1 && data->ceiling_color != -1)
		handle_error(data, ENOEXEC,
			"Invalid color.\tMultiple ceiling colors found.");
	rgb = get_color(line + 1);
	if (rgb == -1)
		handle_error(data, ENOEXEC, "Invalid color.");
	if (i == 0)
		data->floor_color = rgb;
	else
		data->ceiling_color = rgb;
	return (0);
}
