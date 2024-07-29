SRC = main.c philo_init.c utils.c philo_actions.c philo_helpers.c simulation.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC_FLAGS = -Wall -Wextra -Werror
CC = cc

NAME = philo

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CC_FLAGS) $(OBJ) -o $@ -lpthread #-fsanitize=thread #-fsanitize=adress

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re