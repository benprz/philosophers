#MAKEFLAGS += --silent

NAME = philo
CC = gcc
CFLAGS = -g #-Wall -Wextra -Werror -Wpedantic 
INC_DIR = includes/
INC = 

SRC_DIR = ./
SRC =	main.c

LIBRARY_DIR = ./

LIBFT_DIR = $(LIBRARY_DIR)libft/
LIBFT_INC_DIR = $(LIBFT_DIR)includes/
LIBFT_INC = -I $(LIBFT_INC_DIR) $(LIBFT_DIR)libft.a

OBJ_DIR = .obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

ARGS = 2 500 100 100

.PHONY : all clean fclean re $(LIBFT_DIR) exec

all: $(LIBFT_DIR) $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_INC) -I $(INC_DIR) -lm

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(INC_DIR),$(INC))
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_INC_DIR) -I $(INC_DIR)

$(LIBFT_DIR):
	$(MAKE) -C $(LIBFT_DIR)

exec: all
	./$(NAME) $(ARGS)

norm:
	norminette $(SRC_DIR)$(SRC) $(INC_DIR)$(INC)

clean:
	/bin/rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	/bin/rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all
