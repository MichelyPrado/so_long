NAME		=	so_long

GNL_PATH	=	GNL/

GNL_FILES	=	get_next_line_utils.c get_next_line.c ft_itoa.c
GNL_OBJS	=	$(addprefix $(GNL_PATH), $(GNL_FILES:.c=.o))

FILES		=	1_main.c 2_init_game.c 3_init_map.c 4_show_map.c 5_valid_path.c 6_test_path.c
OBJS		=	$(FILES:.c=.o)

CFLAGS		=	-Wall -Werror -Wextra -g3

MLX_FLAGS	=	-lmlx -lX11 -Imlx -lXext

%.o: %.c 
	cc $(CFLAGS) -c $<  -o $@
	
all: $(NAME)

$(NAME): $(GNL_OBJS) $(OBJS)
	cc $(CFLAGS) $^ $(MLX_FLAGS) -o $@

clean: 
	rm -f $(GNL_OBJS) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

val:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=teste -s ./so_long maps/map43.ber

norm:
	@printf "\n\nNorminette simples\n\n"
	@norminette
	@printf "\n\nNorminette -R CheckHeader\n\n"
	@norminette -R CheckHeader
	@printf "\n\nNorminette -R CheckDefine\n\n"
	@norminette -R CheckDefine
