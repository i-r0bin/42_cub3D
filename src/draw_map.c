#include "cub3d.h"

void    draw_point(t_data *data, int x, int y)
{
    int i;
    int j;
    
    set_param(&x, &y, data);
    i = 0;
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            if (x + j > data->img_width || y + i > data->img_height || x < 0 || y < 0)
                break;
            int radius = MAP_SIZE / 4;
            int dx = j - MAP_SIZE / 2;
            int dy = i - MAP_SIZE / 2;
            if (dx * dx + dy * dy <= radius * radius)
                data->img_addr[(y + i) * data->img_width + (x + j)] = 0xff0000; //red
            j++;
        }
        i++;
    }
}

void    draw_floor(t_data *data, int x, int y)
{
    int i;
    int j;

    set_param(&x, &y, data);
    i = 0;
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            if (x + j > data->img_width || y + i > data->img_height || x < 0 || y < 0)
                break;
            if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1)
                data->img_addr[(y + i) * data->img_width + (x + j)] = 0x000000; //black
            else
                data->img_addr[(y + i) * data->img_width + (x + j)] = data->floor_color;
            j++;
        }
        i++;
    }
}

void    draw_borders(t_data *data, int x, int y)
{
    int i;
    int j;
    
    set_param(&x, &y, data);
    i = 0;
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            if (!(x + j > data->img_width || y + i > data->img_height || x < 0 || y < 0))
                data->img_addr[(y + i) * data->img_width + (x + j)] = data->ceiling_color;
            j++;
        }
        i++;
    }
}

void    draw_map(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width)
        {
            if (data->map[y][x] == '1')
                draw_borders(data, x, y);
            else if (data->map[y][x] == '0' || data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'W' || data->map[y][x] == 'E')
                draw_floor(data, x, y);
            x++;
        }
        y++;
    }
    draw_point(data, data->player_x, data->player_y);
}
