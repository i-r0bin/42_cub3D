#include "cub3d.h"
#include <math.h>

void render_cub(t_data *data)
{
    int w = data->img_width;
    int h = data->img_height;

    // Main loop for rendering each vertical stripe
    for (int x = 0; x < w; x++)
    {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)w - 1; // x-coordinate in camera space
        double rayDirX = data->dir_x + data->plane_x * cameraX;
        double rayDirY = data->dir_y + data->plane_y * cameraX;

        // Initial map square and ray distances
        int mapX = (int)data->player_x;
        int mapY = (int)data->player_y;
        double sideDistX, sideDistY;

        // Calculate delta distances
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;

        // Step direction and initial side distances
        int stepX, stepY;
        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or an EW wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->player_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->player_x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->player_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->player_y) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0)
        {
            // Jump to the next map square, either in x-direction, or y-direction
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
            // Check if ray has hit a wall
            if (data->map[mapY][mapX] == '1')
                hit = 1;
        }

        // Calculate the perpendicular distance to the wall
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        // Calculate height of line to draw on screen
        int lineHeight = (int)(h / perpWallDist);

        // Calculate lowest and highest pixel to fill in the current stripe
        int pitch = 100;
        int drawStart = -lineHeight / 2 + h / 2 + pitch;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2 + pitch;
        if (drawEnd >= h) drawEnd = h - 1;

        // Texturing calculations
        int texNum = data->map[mapY][mapX] - '1'; // Convert map value to texture index
        double wallX; // Exact position of wall hit
        if (side == 0) wallX = data->player_y + perpWallDist * rayDirY;
        else           wallX = data->player_x + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        // X coordinate on the texture
        int texX = (int)(wallX * (double)TEXTURE_SIZE);
        if (side == 0 && rayDirX > 0) texX = TEXTURE_SIZE - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEXTURE_SIZE - texX - 1;

        // Step size and starting texture position
        double step = 1.0 * TEXTURE_SIZE / lineHeight;
        double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;

        // Draw the pixels of the stripe
        for (int y = drawStart; y < drawEnd; y++)
        {
            int texY = (int)texPos & (TEXTURE_SIZE - 1);
            texPos += step;

            // Fetch the color from the texture array
            unsigned int color = data->wall_textures[texNum][TEXTURE_SIZE * texY + texX];
            // Make color darker for y-sides (simulate shading)
            if (side == 1) color = (color >> 1) & 0x7F7F7F;
            data->img_addr[y * w + x] = color;
        }
    }
}
