OS=$(shell uname -s)
LINUX = Linux
NAME = fractol

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I./includes

LIBS = -lm 

OBJ_DIR = obj/

LIB_FT = -I./libft -L./libft -lft 

SRCS_DIR = srcs/

SRCS = main.c $(addprefix $(SRCS_DIR), control.c) $(addprefix $(SRCS_DIR), fractal.c)

MINILIBX = -L./minilibxX11/ -I./minilibxX11/ -lmlx -lXext -lX11 

#.PHONY: all clean fclean re

all: $(NAME)


$(NAME): $(SRCS:.c=.o)
	@make -C libft/
#	@make -C minilibxX11
#	$(CC) $(FLAGS) $(MINILIBX) $(INCLUDES) $(LIBS) $(addprefix $(OBJ_DIR),$(notdir $(SRCS:.c=.o))) -o $(NAME)
	$(CC) $(FLAGS) $(addprefix $(OBJ_DIR),$(notdir $(SRCS:.c=.o))) $(LIBS) $(MINILIBX) -o $(NAME)

%.o : %.c
	$(CC) -c $(FLAGS) $(MINILIBX) $(LIB_FT) $(INCLUDES) $(LIBS) $< $(INCLUDES) -o $(addprefix $(OBJ_DIR),$(notdir $@))
	
clean:
#	@make -C minilibxX11 clean
	@make -C libft clean
	/bin/rm -f $(addprefix $(OBJ_DIR),$(notdir $(SRCS:.c=.o)))

fclean: clean
	@make -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all