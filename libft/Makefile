# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riyano <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 12:15:03 by riyano            #+#    #+#              #
#    Updated: 2024/12/09 12:42:56 by riyano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = \
	   ft_isalpha.c ft_isprint.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c ft_atoi.c \
	   ft_putendl_fd.c ft_strlcat.c ft_substr.c ft_bzero.c ft_itoa.c ft_putnbr_fd.c \
	   ft_strlcpy.c ft_tolower.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strlen.c \
	   ft_toupper.c ft_isalnum.c ft_memcmp.c ft_split.c ft_strmapi.c ft_memcpy.c \
	   ft_strchr.c ft_strncmp.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strnstr.c \
	   ft_isdigit.c ft_memset.c ft_striteri.c ft_strrchr.c
BSRCS = \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(BOBJS)
	ar rcs $(NAME) $(OBJS) $(BOBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
