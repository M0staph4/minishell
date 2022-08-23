#include "../inc/header.h"

char *random_file()
{
    static int	random;
    char		*tmp_file;

    random += 2;
    tmp_file = ft_strjoin("/dev/null", ft_itoa(random));
    return (tmp_file); 
}

int    heredoc(t_parser **parse)
{
    int tmp_file;
    char *buff;
    t_parser *parser;
    t_redirection *red;
	tmp_file = -1;

    parser = *parse;
    while (parser)
    {
        red = parser->red; 
        while(red)
        {
            if (red->type == TOKEN_HEREDOC)
            {
                buff = readline("heredoc> ");
    			tmp_file = open(random_file(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (tmp_file < 0)
					tmp_file *= -3;
                while((ft_strncmp(red->file, buff, ft_strlen(buff))))
                {
                    buff = readline("heredoc> ");
		            add_history(buff);
                    ft_putendl_fd(buff, tmp_file);
                }
            }
            red = red->next;
        }
        parser = parser->next;
    }
	return (tmp_file);
} 
