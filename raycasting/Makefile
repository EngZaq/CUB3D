NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

# --- Sources ---
SRCS        = main.c \
              init_mlx.c \
              raycasting.c \
              render.c \
              hooks.c \
              move.c \
			  clean.c

OBJS        = $(SRCS:.c=.o)

# --- MiniLibX Configuration ---
# Change 'mlx' to the actual name of your minilibx folder (e.g., minilibx-linux)
MLX_DIR     = ./minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a

# Detect OS to set library flags correctly
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	# Linux Flags: requires X11 and Xext
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
else
	# MacOS Flags: requires OpenGL and AppKit frameworks
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
endif

# --- Headers ---
INCLUDES    = -I. -I$(MLX_DIR)

# --- Rules ---

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "Done!"

# Compile Object Files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Ensure MLX is compiled if not already
$(MLX_LIB):
	@echo "Compiling MiniLibX..."
	@make -C $(MLX_DIR) > /dev/null

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
	# Optional: Clean MLX too (uncomment if desired)
	# @make -C $(MLX_DIR) clean

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus