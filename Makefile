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
LIBFLAGS = -Imlx -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
NAME = fdf
SRCS = main.c\
	   minilibx.c\
	   minilibx_hooks.c\
	   perth_2Dmap.c\
	   perth_3Dmap.c\
	   perth_fix_size.c\
	   pic_draw_lines1.c\
	   pic_draw_lines2.c\
	   util_atoi.c\
	   util_calloc.c\
	   util_gnl_util.c\
	   util_gnl.c\
	   util_maxmin.c\

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
