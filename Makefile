NAME := so_long

# Imposto all come default goal
.DEFAULT_GOAL := all

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux -Ilibft -O3

# Sources and objects
SRC_DIR := src
OBJ_DIR := obj
MLX_DIR := minilibx-linux
LIBFT_DIR := libft

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT := $(LIBFT_DIR)/libft.a

# Create obj folder if not exists
$(shell mkdir -p $(OBJ_DIR))

# Rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Link rule
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -L$(MLX_DIR) -lmlx_Linux \
	      -L$(LIBFT_DIR) -lft -L/usr/lib -lXext -lX11 -lm -lz \
	      -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
