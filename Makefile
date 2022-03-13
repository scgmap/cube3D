SRC_S    =   main.c position.c init.c raycasting.c make_colors.c clean.c

OBJ_S    =   ${SRC_S:.c=.o}

FLAGS   =   -Wall -Wextra -Werror -I.

NAME	  =	  cube3d

${NAME} :  ${OBJ_S} cube3d.h
			cd ./minilibx/ && make
			gcc $(FLAGS) -L./minilibx/ -lmlx -o $(NAME) \
			$(OBJ_S) -framework OpenGL -framework AppKit

all:	${NAME}

clean:
			rm -f ${OBJ_S}
			cd ./minilibx/ && make clean

fclean:		clean
			rm -f $(NAME)

re:			fclean all

bonus: 		$(NAME)

.PHONY:		all clean fclean re bonus
