#include "../inc/header.h"

void	check_acess(char *path)
{
	if (access(path, F_OK) != 0)
		ft_putstr_fd("File does not exist\n", 2);
	if (access(path, R_OK) != 0)
		ft_putstr_fd("Permission denied\n", 2);
	if (access(path, W_OK) != 0)
		ft_putstr_fd("You have write access\n", 2);
}


int	open_file(char *cmd, char *file, int mode)
{
	if (mode == 1 && access(file, F_OK) == 0)
		return (open(file, O_RDONLY, 0));
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory", 2);
		return (-1);
	}
}
