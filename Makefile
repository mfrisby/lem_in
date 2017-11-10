# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 18:30:39 by mfrisby           #+#    #+#              #
#    Updated: 2017/05/02 16:19:00 by mfrisby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		lem-in

SRCS = 		srcs/lem-in.c srcs/parse_map.c srcs/error_map.c srcs/check_map.c \
			srcs/get_start_room.c srcs/get_end_room.c srcs/get_room_by_name.c \
			srcs/go_fourmi.c srcs/ants.c srcs/get_path.c

INCLUDES = 	-I ./includes

OBJS = $(patsubst srcs/%.c, objs/%.o, $(SRCS))

FLAGS =	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): 	objs $(OBJS)
			@make -C libft/
			@gcc $(FLAGS) -o $(NAME) $(OBJS) ./libft/libft.a
			@echo "\033[32mCompilation OK\033[m"

objs/%.o: 	srcs/%.c
			@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

objs:
			@mkdir -p objs

clean:
	@rm -rf objs
	@echo "\033[33mclean done\033[m"

fclean: 		clean
	@/bin/rm -f $(NAME)
	@echo "\033[33mfclean done\033[m"

libfc:
	@make -C libft/ fclean

re: 			fclean all

.PHONY = 		all clean fclean re
