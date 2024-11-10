#include "cub3d.h"
#include <math.h>

// Main rendering function using raycasting
void render_cub(t_data *data)
{
    int x;

    // Iterate over each vertical stripe of the screen
    for (x = 0; x < data->img_width; x++)
    {
        // Calculate the camera's X-coordinate for the current vertical stripe
        double camera_x = 2 * x / (double)data->img_width - 1;
        double ray_dir_x = data->dir_x + data->plane_x * camera_x;
        double ray_dir_y = data->dir_y + data->plane_y * camera_x;

        // Initialize ray position and map grid coordinates
        int map_x = (int)data->player_x;
        int map_y = (int)data->player_y;

        // Length of ray from current position to next x or y-side
        double side_dist_x;
        double side_dist_y;

        // Length of ray from one x or y-side to the next
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;

        // Direction to move in x and y (+1 or -1)
        int step_x;
        int step_y;
        int hit = 0; // Was a wall hit?
        int side; // Was a NS or EW wall hit?

        // Calculate step and initial sideDist
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (data->player_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - data->player_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->player_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - data->player_y) * delta_dist_y;
        }

        // Perform DDA (Digital Differential Analysis)
        while (hit == 0)
        {
            // Jump to the next map square in x or y direction
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            // Check if the ray has hit a wall
            if (data->map[map_y][map_x] == '1')
                hit = 1;
        }

        // Calculate distance to the point of impact
        if (side == 0)
            perp_wall_dist = (map_x - data->player_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - data->player_y + (1 - step_y) / 2) / ray_dir_y;

        // Calculate the height of the line to draw on the screen
        int line_height = (int)(data->img_height / perp_wall_dist);

        // Calculate the lowest and highest pixel to fill in the current stripe
        int draw_start = -line_height / 2 + data->img_height / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + data->img_height / 2;
        if (draw_end >= data->img_height) draw_end = data->img_height - 1;

        // Choose wall color based on the side
        int wall_color;
        if (side == 0)
            wall_color = 0xFF0000; // Red for NS walls
        else
            wall_color = 0x00FF00; // Green for EW walls

        // Draw the vertical line representing the wall
        for (int y = draw_start; y < draw_end; y++)
        {
            data->img_addr[y * data->img_width + x] = wall_color;
        }
    }
}
