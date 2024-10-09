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
	$Sparse_args.c \
	$Sparse_map.c \
	$Sdraw_map.c \
	$Skey_actions.c \
	$Sutils.c \
	$Serror_handling.c

OBJ = $(SRC:$S%.c=$O%.o)

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
RMDIR = rmdir

all:	$(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

$(MLX):
	make -C $(MLX_PATH) all

$O:
	mkdir -p $@

$(OBJ): | $O

$O%.o: $S%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB) $(INC)

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	$(RM) $(OBJ)
	$(RMDIR) $O

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
