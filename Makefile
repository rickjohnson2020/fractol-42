# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riyano <riyano@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 12:43:55 by riyano            #+#    #+#              #
#    Updated: 2025/02/26 15:44:24 by riyano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCS = srcs/main.c srcs/init.c srcs/render_new.c srcs/event.c srcs/mandelbrot.c \
	   srcs/julia.c srcs/parse.c srcs/utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -march=native -g

BUILD_DIR := build
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.c=.o)))
#OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lmlx -lXext -lX11 -lm -lz

INCLUDES = -I includes -I $(LIBFT_DIR) -I $(MLX_DIR)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(LIBFT_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(BUILD_DIR)/%.o: srcs/%.c includes/fractol.h
	@if [ ! -d $(BUILD_DIR) ]; then mkdir -pv $(BUILD_DIR); fi
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(MLX)

re: fclean all

.PHONY: all clean fclean re
