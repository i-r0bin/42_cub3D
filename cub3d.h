#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>

#define MAP_SIZE 10
#define TILE_SIZE 64
#define TEXTURE_SIZE 64

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    void *img;
    int *img_addr;
    int img_width; // window's width
    int img_height; // window's height
    int bpp; // bits per pixel (number of bits used to store one pixel color)
    int size_l; // size line (number of bytes used to store one line of the image in memory)
    int endian; // endian value (0 or 1) for the image data addr
    char **map;
    int map_width;
    int map_height;
    int player_x;
    int player_y;
    char player_dir;
    double player_speed;
    double player_rot_speed;
    char **wall_textures;
    int floor_color;
    int ceiling_color;
} t_data;

int main(int argc, char **argv);
void    init_data(t_data *data);
void    init_mlx(t_data *data);
void    init_textures(t_data *data);
void    print_controls(void);
void    listen_for_input(t_data *data);
int key_press(int keycode, t_data *data);
int resize_window(t_data *data, XEvent *event);
int cub_exit(t_data *data);
int parse_args(t_data *data, char **av);
int parse_file(t_data *data, int fd);
int parse_line(t_data *data, char *line);
int parse_resolution(t_data *data, char *line);
int parse_texture(t_data *data, char *line, int i);
int parse_color(t_data *data, char *line, int i);
int get_color(char *str);
int parse_map(t_data *data, char *line);
int check_elements(t_data *data);
int handle_error(t_data *data, int err, char *msg);
int err_msg(char *msg, int err);
int render(t_data *data);
int	set_image(t_data *data);
void    draw_map(t_data *data);
void    draw_borders(t_data *data, int x, int y);
void    draw_floor(t_data *data, int x, int y);
void    draw_point(t_data *data, int x, int y);
void    set_zoom(int *x, int *y);
void    set_param(int *x, int *y, t_data *data);
void    cub_free(t_data *data);
void    free_matrix(char **matrix);
char    *line_start(char *line);
void    move_player(t_data *data, char dir);
void    rotate_player(t_data *data, int dir);

#endif