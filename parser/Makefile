NAME				= 	libcb.a

RM					= 	rm -rf

CFLAGS				=	-Wall -Wextra -Werror

LIBFT_DIR			= 	./libft/
LIBFT				= 	$(LIBFT_DIR)libft.a
LIBFT_HED			= 	$(LIBFT_DIR)libft.h

INCLUDES			= 	./includes/
HEADER				= 	$(INCLUDES)cub3d.h

SRCS_DIR			=	./parsing/
SRCS				=	parsing_input_file.c parsing_textures.c \
						parsing_colors_and_player.c parsing_map.c

OBJS_DIR			=	./.objs/
OBJS				=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:%.c=%.o)))

all:				Makefile libft_make $(NAME)

$(NAME):			$(LIBFT) $(OBJS_DIR) $(OBJS)
					ar rc $@ $(OBJS)
					ranlib $@
					@echo "$(CLRCY)create$(CLREL) $@$(CLRRS)"

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c $(HEADER)
					$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
					@mkdir -p $@

clean:
					@-make clean -C $(LIBFT_DIR)
					$(RM) $(OBJS_DIR)

fclean:				clean
					@make fclean -C $(LIBFT_DIR)
					$(RM) $(NAME)
					@$(RM) .gitpush

re:					fclean all

libft_make:
					@make -C $(LIBFT_DIR)
