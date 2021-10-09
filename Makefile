#MAKEFLAGS += --silent

NAME = philo
CC = gcc
CFLAGS = -g #-Wall -Wextra -Werror -Wpedantic 
INC_DIR = includes/
INC = 

SRC_DIR = ./
SRC =	main.c

OBJ_DIR = .obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

ARGS = 2 500 100 100

.PHONY : all clean fclean re $(LIBFT_DIR) exec

all: $(LIBFT_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I $(INC_DIR) -lm

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(INC_DIR),$(INC))
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

exec: all
	./$(NAME) $(ARGS)

norm:
	norminette $(SRC_DIR)$(SRC) $(INC_DIR)$(INC)

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all
