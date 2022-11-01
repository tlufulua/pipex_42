NAME		=	pipex
CC			=	@gcc
CFLAGS		=	-Wall -Werror -Wextra -I $(INC) -I $(LIBFT_INC)
INC			=	inc/
LIBFT_DIR	=	$(INC)libft/
LIBFT_INC	=	$(LIBFT_DIR)inc/
LIBFT		=	$(LIBFT_DIR)libft.a
SRCS_DIR	=	srcs/
SRCS		=	ex_dup.c
MAIN		=	$(SRCS_DIR)pipex.c
OBJS		=	$(MAIN:%.c=%.o) $(addprefix $(SRCS_DIR), $(SRCS:%.c=%.o))

all:	$(NAME)

%.o:	%.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)

clean:
		@find . -name ".DS_Store" -delete
		@find . -name "*.swp" -delete
		@find . -name "*.o" -delete
		@find . -name "*.gch" -delete
		@make clean -C $(LIBFT_DIR)

fclean:	clean
		@find . -name "$(NAME)" -delete
		@make fclean -C $(LIBFT_DIR)

re:	fclean all
