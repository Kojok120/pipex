# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kokamoto <kojokamo120@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 22:35:55 by kokamoto          #+#    #+#              #
#    Updated: 2025/01/13 14:53:00 by kokamoto         ###   ########.fr        #
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

# オブジェクトファイルのパスを修正
OBJS = $(SRCS:%.c=obj/%.o)
INCLUDES = -I./includes -I./src/utils

# オブジェクトファイルの依存するディレクトリを作成
OBJDIRS = obj/src/utils obj/src

all: $(NAME)

# ディレクトリの作成とコンパイルを順番に実行
$(NAME): $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# オブジェクトファイルの生成規則
obj/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 必要なディレクトリを作成
$(OBJDIRS):
	mkdir -p $(OBJDIRS)

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
