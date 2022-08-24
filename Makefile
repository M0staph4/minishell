NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline -fsanitize=address -g
SRC = minishell.c lexer/lexer.c lexer/tokenizer.c parser/parser.c parser/redirections.c parser/parser_tools.c \
		exec/builtins/exec_env.c exec/builtins/exec_cd.c exec/builtins/exec_pwd.c exec/pipeline.c exec/path_utils.c \
		lexer/collect_lexer.c lexer/lexer_tools.c lexer/syntax.c exec/redirections.c exec/builtins/exec_export.c \
		exec/builtins/exec_echo.c exec/builtins/exec_unset.c exec/builtins/exec_exit.c exec/heredoc.c
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
fclean: clean
	@echo "${_BOLD}${_RED}---------Deleting---------${_END}"
	rm -rf $(NAME)
	rm -rf $(LIB)
	rm -rf libft/libft.a
	rm -rf minishell.dSYM


re: fclean all