NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

MLX_DIR     = ./minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a
LIBFT_DIR   = ./Libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

SRCS        = main.c \
              init.c \
              init_mlx.c \
              hooks.c \
              move.c \
              render.c \
              raycasting.c \
              clean.c \
              parse_info.c \
              parse_map.c \
              check_map.c \
              parse_utils.c \
              get_next_line.c

OBJS        = $(SRCS:.c=.o)


INCLUDES    = -I. -I$(MLX_DIR) -I$(LIBFT_DIR)
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft


all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "Done!"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
	@echo "Building MiniLibX..."
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(LIBFT_LIB):
	@echo "Building Libft..."
	@make -C $(LIBFT_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re