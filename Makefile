# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riyano <riyano@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 12:43:55 by riyano            #+#    #+#              #
#    Updated: 2025/02/17 13:13:36 by riyano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCS := main.c init.c fractal.c event.c \

OBJS := $(SRCS:.c = .o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lmlx -lXext -lX11 -lm -lz

INCLUDES = -I includes -I $(LIBFT_DIR) -I $(MLX_DIR)

RM = rm -fi

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

%.o: %.c fractol.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(MLX)

re: fclean all

.PHONY: all clean fclean re
