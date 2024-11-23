#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

# define MAP_SIZE 10
# define TILE_SIZE 64
# define TEXTURE_SIZE 64

typedef struct s_color_table_entry
{
	char				*symbol;
	unsigned int		color;
}						t_color_table_entry;

typedef struct s_texture
{
	char				*path;
	int					width;
	int					height;
	int					colors_num;
	int					char_per_pixel;
	t_color_table_entry	*color_table;
	unsigned int		**color_matrix;
}						t_texture;

typedef struct s_player
{
	int x;            // Player's x position
	int y;            // Player's y position
	double dir_x;     // Player's direction vector X
	double dir_y;     // Player's direction vector Y
	double plane_x;   // Camera plane vector X
	double plane_y;   // Camera plane vector Y
	double speed;     // Player's movement speed
	double rot_speed; // Player's rotation speed
}						t_player;

typedef struct s_map
{
	char				**map;
	int					width;
	int					height;
}						t_map;

typedef struct s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img;
	int					*img_addr;
	int					img_width;
	int					img_height;
	int					bpp;
	// bits per pixel (number of bits used to store one pixel color)
	int					size_l;
	// size line (number of bytes used to store one line of the image in memory)
	int endian; // endian value (0 or 1) for the image data addr
}						t_mlx;

typedef struct s_data
{
	t_mlx				mlx;
	t_map				map;
	t_player			player;
	char				starting_dir;
	t_texture			north_texture;
	t_texture			south_texture;
	t_texture			west_texture;
	t_texture			east_texture;
	int					floor_color;
	int					ceiling_color;
}						t_data;

void					print_controls(void);

// main and init
int						main(int argc, char **argv);
void					init_data(t_data *data);
void					init_mlx(t_data *data);
void					init_textures(t_data *data);
void					listen_for_input(t_data *data);
int						render(t_data *data);

// parser
int						parse_args(t_data *data, char **av);
int						parse_file(t_data *data, int fd);
int						parse_line(t_data *data, char *line);
int						save_texture_path(t_data *data, char *line);
int						parse_color(t_data *data, char *line, int i);
int						parse_map(t_data *data, char *line);
int						parse_textures(t_data *data);

// parse texture files
int						parse_texture_data(t_data *data, t_texture *texture);
void					parse_texture_info(char *line, t_texture *texture,
							t_data *data);
void					parse_color_table(t_data *data, t_texture *texture,
							int fd);
void					parse_color_matrix(t_data *data, t_texture *texture,
							int fd);
unsigned int			*get_color_row(t_data *data, t_texture *texture,
							char *line);
unsigned int			get_color_by_symbol(t_texture *texture, char *symbol);

// format colors
int						get_color_from_rgb_str(char *str);
unsigned int			get_color_from_rgb_array(char **rgb);
unsigned int			ft_atoi_hex(char *str);
int						hex_char_to_int(char c);

// check data
int						check_elements(t_data *data);
int						check_textures(t_data *data);
int						check_colors(t_data *data);
int						check_texture_format(char *format);
int						is_texture(char *line);
int						check_file_path(t_data *data, char *path);

// draw map
int						set_image(t_data *data);
void					draw_map(t_data *data);
void					draw_borders(t_data *data, int x, int y);
void					draw_floor(t_data *data, int x, int y);
void					draw_point(t_data *data, int x, int y);

// raycasting
void					render_cub(t_data *data);
unsigned int			get_color_from_texture(t_data *data, int texNum,
							int texX, int texY);

// key actions
int						key_press(int keycode, t_data *data);
void					move_player(t_data *data, char dir);
void					rotate_player(t_data *data, int dir);
int						resize_window(t_data *data, XEvent *event);
int						cub_exit(t_data *data);

// utils
char					*line_start(char *line);
void					set_zoom(int *x, int *y);
void					cub_free(t_data *data);
void					free_matrix(char **matrix);
void					free_texture(t_texture *texture);
char					**ft_strtrim_split_args(char **strs, char *set);
int						ft_isdigit_split_args(char **strs);

// error handling
int						handle_error(t_data *data, int err, char *msg);
int						err_msg(char *msg, int err);

#endif