S = src/
O = obj/
I = ./
LIBFT_PATH = ./libft/
MLX_PATH = ./minilibx-linux/
LIBFT = $(LIBFT_PATH)libft.a
MLX = $(MLX_PATH)libmlx.a
LIB = -L$(LIBFT_PATH) -L$(MLX_PATH) -lft -lmlx -lXext -lX11 -lm
INC = -I$I -I$(LIBFT_PATH) -I$(MLX_PATH)

SRC = \
	$Smain.c \
	$Sinit_data.c \
	$Skey_actions.c \
	$Sparse_args.c \
	$Sparse_map.c \
	$Sparse_texture.c \
	$Scolor.c \
	$Scolor_utils.c \
	$Sdraw_map.c \
	$Srender_cub.c \
	$Sutils.c \
	$Svalidate_data.c \
	$Serror_handling.c \

OBJ = $(SRC:$S%.c=$O%.o)

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
RMDIR = rmdir

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

$(MLX):
	# Ensure MinilibX is extracted before building
	echo "Extracting MinilibX..."; \
	tar xf minilibx-linux.tgz -C .; \
	make -C $(MLX_PATH) all

$O:
	mkdir -p $@

$(OBJ): | $O

$O%.o: $S%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB) $(INC)

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	$(RM) $(OBJ)
	if [ -d $O ]; then $(RMDIR) $O; fi

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)
	echo "Deleting MinilibX..."; \
	rm -rf minilibx-linux.tgz -C .; \

re: fclean all

format:
	@c_formatter_42 $(S)*.c cub3d.h

.PHONY: all clean fclean re extract format
