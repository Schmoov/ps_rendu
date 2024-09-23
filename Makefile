CC := cc -Wall -Wextra -Werror
CFLAGS :=

NAME := push_swap
LIBFT := libft/libft.a

SRC_DIR := src/
SRC := $(filter-out $(wildcard $(SRC_DIR)main*.c), $(wildcard $(SRC_DIR)*.c))

OBJ_DIR := .obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all: $(NAME)

bonus: checker

$(NAME): $(OBJ) $(LIBFT) src/main_ps.c
	$(CC) $(CFLAGS) $^ -o $@

checker: src/main_checker.c $(OBJ) $(LIBFT) 
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft/

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f checker

re: fclean all

:PHONY all bonus clean fclean re
