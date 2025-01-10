# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kokamoto <kokamoto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 22:35:55 by kokamoto          #+#    #+#              #
#    Updated: 2025/01/10 22:03:16 by kokamoto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/pipe.c \
       src/here_doc.c \
       src/command.c \
       src/main.c \
       src/error.c \
       src/utils/ft_strlen.c \
       src/utils/ft_strchr.c \
       src/utils/ft_strjoin.c \
       src/utils/get_next_line.c \
       src/utils/ft_split.c \
       src/utils/ft_substr.c \
       src/utils/ft_strncmp.c \
       src/utils/ft_strdup.c \
       src/utils/ft_strcmp.c \
	src/utils/ft_strlcpy.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes -I./src/utils

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all