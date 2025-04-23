# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roberto                                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23                                #+#    #+#              #
#    Updated: 2025/04/23                                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux -O3

# Sources and objects
SRC_DIR := src
OBJ_DIR := obj
MLX_DIR := minilibx-linux

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Create obj folder if not exists
$(shell mkdir -p $(OBJ_DIR))

# Rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link rule
$(NAME): $(OBJ)
	$(CC) $(OBJ) -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
