OS=$(shell uname -s)
LINUX = Linux
NAME = fractol
CC = gcc
FLAGS = -Wall -Wextra -Werror -g -O3
INCLUDES = -I./includes
LIBS = -lm -lpthread -pthread
OBJ_DIR = obj/
LIB_FT = -I./libft -L./libft -lft 
SRCS_DIR = srcs/
SRCS =  fractal.c main.c control.c
MINILIBX = -L./minilibxX11/ -I./minilibxX11/ -lmlx -lXext -lX11 
.PHONY: all clean fclean re

all: $(NAME) 

ft :

$(NAME):  $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
	@make -C libft/
	@make -C minilibxX11/ -f Makefile.gen
	$(CC) $(FLAGS) $(addprefix $(OBJ_DIR),$(SRCS:.c=.o)) $(LIB_FT) $(LIBS) $(MINILIBX) -o $(NAME)

$(addprefix $(OBJ_DIR), %.o) : $(addprefix $(SRCS_DIR),%.c) $(wildcard)
	$(CC) -c -MMD $(FLAGS) $(MINILIBX) $(LIB_FT) $(INCLUDES) $(LIBS) $< -o $@

clean:
	@make -C minilibxX11 clean
	@make -C libft clean
	/bin/rm -f $(addprefix $(OBJ_DIR),*)

fclean: clean
	@make -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

include $(wildcard $(OBJ_DIR)*.d) 