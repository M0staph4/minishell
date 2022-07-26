NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
SRC = minishell.c lexer/lexer.c lexer/tokenizer.c parser/parser.c
LIB = libft.a

# This is a minimal set of ANSI/VT100 color codes
_END=$'\x1b[0m'
_BOLD=$'\x1b[1m'

# Colors
_RED=$'\x1b[31m'
_GREEN=$'\x1b[32m'
_CYAN=$'\x1b[36m'


all : $(NAME)

$(LIB):
	@echo "${_BOLD}${_CYAN}---------Libft Compilation---------${_END}"
	make -C libft --silent
	cp libft/libft.a ./

$(NAME): $(SRC) $(LIB)
	@echo "${_BOLD}${_GREEN}---------Minishell Compilation---------${_END}"
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LIB)
clean:
	@echo "${_BOLD}${_RED}---------Cleaning Objects---------${_END}"
	rm -rf $(OBJ)
	rm -rf libft/*.o
fclean:
	@echo "${_BOLD}${_RED}---------Deleting---------${_END}"
	rm -rf $(NAME)
	rm -rf $(LIB)
	rm -rf libft/libft.a

re: fclean all