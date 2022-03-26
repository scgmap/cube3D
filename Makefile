SRC_S    =   main.c position.c position2.c init.c init2.c raycasting.c \
			make_colors.c clean.c

OBJ_S    =   ${SRC_S:.c=.o}

SRC_P	=	./parser/parsing/parsing_map.c ./parser/parsing/parsing_textures.c \
	./parser/parsing/parsing_colors_and_player.c \
	./parser/parsing/parsing_input_file.c

%.o: %.c
			gcc -Wall -Wextra -Werror -Imlx -c $< -o $@

FLAGS   =   -Wall -Wextra -Werror

NAME	  =	  cub3D

${NAME} :  ${OBJ_S} ${SRC_P} ./parser/Includes/cub3d.h cube3d.h
			cd ./mlx/ && make
			cd ./parser/ && make
			gcc $(FLAGS) -L./parser/libft/ -L./parser/ -Lmlx -lmlx -lcb -lft\
			  $(OBJ_S) -framework OpenGL -framework AppKit -o $(NAME)

all:	${NAME}

clean:
			rm -f ${OBJ_S}
			cd ./mlx/ && make clean
			cd ./parser/ && make clean

fclean:		clean
			cd ./parser/ && make fclean
			rm -f $(NAME)

re:			fclean all

bonus: 		$(NAME)

.PHONY:		all clean fclean re bonus
