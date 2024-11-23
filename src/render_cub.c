#include "cub3d.h"
#include <math.h>

void	render_cub(t_data *data)
{
	int				w;
	int				h;
	double			rayDirX;
	double			rayDirY;
	int				mapX;
	int				mapY;
	double			deltaDistX;
	double			deltaDistY;
	double			perpWallDist;
	int				lineHeight;
	int				pitch;
	int				drawStart;
	int				drawEnd;
	int				texX;
	double			step;
	double			texPos;
	int				texY;
	unsigned int	color;
	int				texNum;
	double			wallX;

	w = data->mlx.img_width;
	h = data->mlx.img_height;
	// Main loop for rendering each vertical stripe
	for (int x = 0; x < w; x++)
	{
		// Calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; // x-coordinate in camera space
		rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
		rayDirY = data->player.dir_y + data->player.plane_y * cameraX;
		// Initial map square and ray distances
		mapX = (int)data->player.x;
		mapY = (int)data->player.y;
		double sideDistX, sideDistY;
		// Calculate delta distances
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		// Step direction and initial side distances
		int stepX, stepY;
		int hit = 0; // Was there a wall hit?
		int side;    // Was a NS or an EW wall hit?
		// Calculate step and initial sideDist
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
		// Perform DDA
		while (hit == 0)
		{
			// Jump to the next map square, either in x-direction,
			// or y-direction
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
			if (data->map.map[mapY][mapX] == '1')
				hit = 1;
		}
		// Calculate the perpendicular distance to the wall
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		// Calculate height of line to draw on screen
		lineHeight = (int)(h / perpWallDist);
		// Calculate lowest and highest pixel to fill in the current stripe
		pitch = 100;
		drawStart = -lineHeight / 2 + h / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + h / 2 + pitch;
		if (drawEnd >= h)
			drawEnd = h - 1;
		// Texturing calculations
		texNum = data->map.map[mapY][mapX] - '1';
		// Convert map value to texture index
		// Exact position of wall hit
		if (side == 0)
			wallX = data->player.y + perpWallDist * rayDirY;
		else
			wallX = data->player.x + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		// X coordinate on the texture
		texX = (int)(wallX * (double)TEXTURE_SIZE);
		if (side == 0 && rayDirX > 0)
			texX = TEXTURE_SIZE - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEXTURE_SIZE - texX - 1;
		// Step size and starting texture position
		step = 1.0 * TEXTURE_SIZE / lineHeight;
		texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
		// Draw the pixels of the stripe
		for (int y = drawStart; y < drawEnd; y++)
		{
			texY = (int)texPos & (TEXTURE_SIZE - 1);
			texPos += step;
			// Fetch the color from the texture file stored in data->wall_textures.*
			color = get_color_from_texture(data, texNum, texX, texY);
			// Make color darker for y-sides (simulate shading)
			if (side == 1)
				color = (color >> 1) & 0x7F7F7F;
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
