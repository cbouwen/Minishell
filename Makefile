NAME = Minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRC = main.c env_parser.c utils.c env_utils.c tester.c
SRC_DIR = ./src/
SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))


LIBFT_DIR = ./lib/Libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
LIBFT_INC = -I $(LIBFT_DIR)

PRINTF_DIR = ./lib/Printf/
PRINTF_LIB = $(PRINTF_DIR)printf.a
PRINTF_INC = -I $(PRINTF_DIR)

all : $(NAME)

$(NAME) : $(LIBFT_LIB) $(PRINTF_LIB) $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) $(LIBFT_LIB) $(PRINTF_LIB) -o $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)

clean : 
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)

fclean : clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
