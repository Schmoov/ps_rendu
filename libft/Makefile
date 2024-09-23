NAME := libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror 

SRC_DIR := src/
SRC :=ft_ctype/ft_isalnum.c ft_ctype/ft_isalpha.c ft_ctype/ft_isascii.c ft_ctype/ft_isdigit.c ft_ctype/ft_isprint.c ft_ctype/ft_tolower.c ft_ctype/ft_toupper.c ft_ints/ft_ibsearch.c ft_ints/ft_imath.c ft_ints/ft_isort.c ft_ints/ft_iswap.c ft_lst/ft_lstadd_back.c ft_lst/ft_lstadd_front.c ft_lst/ft_lstclear.c ft_lst/ft_lstdelone.c ft_lst/ft_lstiter.c ft_lst/ft_lstlast.c ft_lst/ft_lstmap.c ft_lst/ft_lstnew.c ft_lst/ft_lstsize.c ft_printf/ft_printf.c ft_printf/ft_printf_utils.c ft_printf/int_printers.c ft_printf/itoa_base.c ft_printf/parser.c ft_printf/printer_utils1.c ft_printf/printer_utils2.c ft_printf/ptr_printers.c ft_printf/tokenizer.c ft_stdio/ft_putchar_fd.c ft_stdio/ft_putendl_fd.c ft_stdio/ft_putnbr_fd.c ft_stdio/ft_putstr_fd.c ft_stdio/get_next_line.c ft_stdlib/ft_atoi.c ft_stdlib/ft_calloc.c ft_stdlib/ft_free_split.c ft_stdlib/ft_itoa.c ft_string/ft_bzero.c ft_string/ft_memchr.c ft_string/ft_memcmp.c ft_string/ft_memcpy.c ft_string/ft_memmove.c ft_string/ft_memset.c ft_string/ft_split.c ft_string/ft_strchr.c ft_string/ft_strdup.c ft_string/ft_striteri.c ft_string/ft_strjoin.c ft_string/ft_strlcat.c ft_string/ft_strlcpy.c ft_string/ft_strlen.c ft_string/ft_strmapi.c ft_string/ft_strncmp.c ft_string/ft_strnstr.c ft_string/ft_strrchr.c ft_string/ft_strtrim.c ft_string/ft_substr.c
OBJ_DIR := .obj/
OBJ := $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))
###############################################################################

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $?

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
