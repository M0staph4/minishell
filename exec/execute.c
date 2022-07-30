#include "../inc/header.h"
#include "../inc/execution.h"

void	execute(t_parser **parse)
{
    if (!ft_strncmp((*parse)->args[0], "cd", 3))
        exec_cd((*parse)->args[1]);
    else if (!ft_strncmp((*parse)->args[0], "pwd", 4))
        exec_pwd();
}