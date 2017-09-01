NAME =	lem_in

SRCS = 	srcs/main.c \

OBJS = 	$(patsubst srcs/%.c, objs/%.o, $(SRCS))

INCS = -I ./includes ./libft/includes/

FLAGS =	-Wall -Wextra -Werror

CC =	gcc

all: $(NAME)

$(NAME):	objs $(OBJS)
			@make -C libft
			@$(CC) $(FLAGS) -o $(NAME) $(OBJS) libft/libft.a
			@echo "\033[32mCompilation OK\033[m"

objs/%.o:	srcs/%.c
			@$(CC) $(FLAGS) $(INCS) -o $@ -c $<

objs:
			@mkdir -p objs

clean:
	@rm -rf $(OBJS)
	@rm -rf lem_in.dSYM
	@make -C libft/ clean
	@echo "\033[33mclean done\033[m"

fclean: 		clean
	@make -C ./libft fclean
	@/bin/rm -f $(NAME)
	@echo "\033[33mfclean done\033[m"

re: 			fclean all

.PHONY = 		all clean fclean re