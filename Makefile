# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/04 14:00:12 by natakaha          #+#    #+#              #
#    Updated: 2025/11/04 14:00:12 by natakaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -Imlx -Lminilibx_linux -lmlx_Linux -lX11 -lXext -lm
NAME =  fdf
SRCS = get_next_line.c\
	   get_next_line_utils.c\
	   perth.c\
	   util_perth.c\
	   main.c\
	   process.c\
	   make_display.c\
	   lines.c\
	   util_lines.c\

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

bonus: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
