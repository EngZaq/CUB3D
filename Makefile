# Program name
NAME = cub3d

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# --- Libft ---
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

# --- MiniLibX ---
# You may need to change this path depending on your system
MLX_DIR = /usr/local/lib
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11
MLX_INC = -I/usr/local/include

# --- Math Library ---
MATH_FLAGS = -lm

# All include flags
INC_FLAGS = -I. $(LIBFT_INC) $(MLX_INC)

# All linker flags
L_FLAGS = $(LIBFT_A) $(MLX_FLAGS) $(MATH_FLAGS)

# --- Source Files ---
# Add your .c files here as you create them
SRCS = main.c \
       parse_file.c \
       error.c \
       check_file_extension.c \
       init_data.c \
	   parse_config.c \
	   parse_map.c \
	   file.c



# Object files
OBJS = $(SRCS:.c=.o)

# --- Rules ---

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(L_FLAGS) -o $(NAME)

# Rule to build libft
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile .c files to .o files
%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re