#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307
#define MAP_SIZE 10
#define TILE_SIZE 64
#define TEXTURE_SIZE 64
#define ERR_USAGE 1
#define ERR_FILE 2
#define ERR_RES 3
#define ERR_TEX 4
#define ERR_COLOR 5
#define ERR_MAP 6

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    void *img;
    int *img_addr;
    int img_width; // window's width
    int img_height; // window's height
    char **map;
    int map_width;
    int map_height;
    int bpp; // bits per pixel (number of bits used to store one pixel color)
    int size_l; // size line (number of bytes used to store one line of the image in memory)
    int endian; // endian value (0 or 1) for the image data addr
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
void init_data(t_data *data);
int parse_args(t_data *data, char **av);
int parse_file(t_data *data, int fd);
int parse_line(t_data *data, char *line);
int parse_resolution(t_data *data, char *line);
int parse_texture(t_data *data, char *line, int i);
int parse_color(t_data *data, char *line, int i);
int parse_map(t_data *data, char *line);
void init_mlx(t_data *data);
void init_textures(t_data *data);
void print_controls(void);
void listen_for_input(t_data *data);
int key_press(int keycode, t_data *data);
int close_win(t_data *data);
int get_wall_color(t_data *data, int x, int y, int i, int j);
int get_texture_color(t_data *data, char *texture, int x, int y);
int get_pixel_color(t_data *data, char *texture, int x, int y);
int get_color(t_data *data, char *texture, int x, int y);
int err_msg(char *msg, int err, int ret);
void    draw_map(t_data *data);
void    draw_borders(t_data *data, int x, int y);
void    draw_floor(t_data *data, int x, int y);
void    draw_point(t_data *data, int x, int y);
void    draw_map(t_data *data);
void    set_zoom(int *x, int *y);
void    set_param(int *x, int *y, t_data *data);
void    free_matrix(char **matrix);
void    cub_free(t_data *data);
void    move_player(t_data *data, char dir);
void    rotate_player(t_data *data, int dir);

#endif