#include "cub3d.h"
#include <math.h>

void render_cub(t_data *data)
{
    int w = data->mlx.img_width;
    int h = data->mlx.img_height;

    // Draw floor and ceiling
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (y < h / 2)
                data->mlx.img_addr[y * w + x] = data->ceiling_color; // Ceiling
            else
                data->mlx.img_addr[y * w + x] = data->floor_color;   // Floor
        }
    }

    // Render walls
    for (int x = 0; x < w; x++)
    {
        double cameraX = 2 * x / (double)w - 1;
        double rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
        double rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

        int mapX = (int)data->player.x;
        int mapY = (int)data->player.y;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);

        double sideDistX, sideDistY;
        int stepX, stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->player.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->player.y) * deltaDistY;
        }

        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (data->map.map[mapY][mapX] == '1')
                hit = 1;
        }

        double perpWallDist = (side == 0)
            ? (mapX - data->player.x + (1 - stepX) / 2) / rayDirX
            : (mapY - data->player.y + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(h / perpWallDist);
        int drawStart = -lineHeight / 2 + h / 2;
        int drawEnd = lineHeight / 2 + h / 2;

        if (drawStart < 0)
            drawStart = 0;
        if (drawEnd >= h)
            drawEnd = h - 1;

        double wallX = (side == 0)
            ? data->player.y + perpWallDist * rayDirY
            : data->player.x + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)TEXTURE_SIZE);
        if (side == 0 && rayDirX > 0)
            texX = TEXTURE_SIZE - texX - 1;
        if (side == 1 && rayDirY < 0)
            texX = TEXTURE_SIZE - texX - 1;

        double step = 1.0 * TEXTURE_SIZE / lineHeight;
        double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

        for (int y = drawStart; y < drawEnd; y++)
        {
            int texY = (int)texPos & (TEXTURE_SIZE - 1);
            texPos += step;

            int texNum = data->map.map[mapY][mapX] - '1';
            unsigned int color = get_color_from_texture(data, texNum, texX, texY);

            if (side == 1)
                color = (color >> 1) & 0x7F7F7F; // Darken for shading

            data->mlx.img_addr[y * w + x] = color;
        }
    }
}


unsigned int	get_color_from_texture(t_data *data, int texNum, int texX,
		int texY)
{
	unsigned int	color;

	if (texNum == 0)
		color = data->north_texture.color_matrix[texY][texX];
	else if (texNum == 1)
		color = data->south_texture.color_matrix[texY][texX];
	else if (texNum == 2)
		color = data->west_texture.color_matrix[texY][texX];
	else if (texNum == 3)
		color = data->east_texture.color_matrix[texY][texX];
	else
		color = 0x00FF00;
	return (color);
}
