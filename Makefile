CC := cc -g
CFLAGS := 

NAME := push_swap
LIBFT := libft/libft.a

SRC_DIR := src/
SRC := $(filter-out $(wildcard $(SRC_DIR)main*.c), $(wildcard $(SRC_DIR)*.c))

OBJ_DIR := .obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

TEST_SRC_DIR := test/src/
TEST_SRC := $(wildcard $(TEST_SRC_DIR)*.c)
TEST_OBJ := $(patsubst $(TEST_SRC_DIR)%.c, $(OBJ_DIR)%.o, $(TEST_SRC))

TEST_BIN_DIR := test/bin/
TEST_BIN := $(patsubst $(OBJ_DIR)%.o, $(TEST_BIN_DIR)%, $(TEST_OBJ))

CRIT := -lcriterion
ASAN := -fsanitize=address
LOG_DIR := .logs/
ASAN_ENV := ASAN_OPTIONS=log_path=$(LOG_DIR):abort_on_error=1:allocator_may_return_null=1

all: $(NAME)

debug : debug
test: $(TEST_BIN)


$(NAME): $(OBJ) $(LIBFT) src/main_ps.c
	$(CC) $(CFLAGS) $^ -o $@

debug: src/main_debug.c $(OBJ) $(LIBFT) 
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN_DIR)%.test: $(OBJ_DIR)%.o $(OBJ_DIR)%.test.o
	@ mkdir -p $(TEST_BIN_DIR)
	@ mkdir -p $(LOG_DIR)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(CRIT) -o $@
	 ./$@

$(TEST_BIN_DIR)%.memtest: $(OBJ_DIR)%.o $(OBJ_DIR)%.memtest.o
	@ mkdir -p $(TEST_BIN_DIR)
	@ mkdir -p $(LOG_DIR)
	$(CC) $(CFLAGS) $(ASAN) $^ $(LIBFT) $(CRIT) -o $@
	$(ASAN_ENV) ./$@

$(OBJ_DIR)%.test.o: $(TEST_SRC_DIR)%.test.c
	@ mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.memtest.o: $(TEST_SRC_DIR)%.memtest.c
	@ mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(ASAN) -c $< -o $@

$(LIBFT):
	make -C libft/

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

rfclean: fclean
	make -C libft/ fclean

re: fclean all

:PHONY all clean fclean re rfclean
