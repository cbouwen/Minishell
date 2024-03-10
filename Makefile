NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -lreadline -fsanitize=address


#ALL SOURCE FILES

SRC_DIR = ./src/
SRC_MAIN = main.c env_parser.c env_utils.c tester.c
SRC_FILES = $(addprefix $(SRC_DIR), $(SRC_MAIN))
UTILS_SRC = $(addprefix $(SRC_DIR)utils/, error_msg.c free.c list_fts.c exit.c signals.c)
TOKENIZER_SRC = $(addprefix $(SRC_DIR)tokenizer/, tokenizer.c token_splitter.c)
LEXER_SRC = $(addprefix $(SRC_DIR)lexer/, lexer.c syntax_check.c)
PARSER_SRC = $(addprefix $(SRC_DIR)parser/, parser.c pipes.c)
EXPANDER_SRC = $(addprefix $(SRC_DIR)expander/, expander.c double_quotes.c utils.c)
EXECUTOR_SRC = $(addprefix $(SRC_DIR)executor/, executor.c echo.c pwd.c env.c export.c export_utils.c)

SRC = $(SRC_FILES) $(UTILS_SRC) $(TOKENIZER_SRC) $(LEXER_SRC) $(PARSER_SRC) $(EXPANDER_SRC) $(EXECUTOR_SRC)


#LIBFT Files

LIBFT_DIR = ./lib/Libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
LIBFT_INC = -I $(LIBFT_DIR)

all : $(NAME)

$(NAME) : $(LIBFT_LIB) $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

clean : 
	make clean -C $(LIBFT_DIR)

fclean : clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
