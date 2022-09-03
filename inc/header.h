#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "execution.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <ctype.h>
# include "struct.h"
# include "sys/stat.h"
# define ERROR 0
# define MALLOC_ERR 1
# define FORK_ERR 2

int	g_exit_status;

typedef struct s_table{
	char	*cmd;
	char	*option;
	char	*args;
}	t_table;

#endif