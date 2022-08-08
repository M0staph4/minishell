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

void	child(int *end, char **argv, char **envp)
{
	char	*path;
	char	**cmd;
	int		fd;

	cmd = ft_split(argv[2], ' ');
	path = search(envp, cmd[0]);
	fd = open_file(cmd[0], argv[1], 1);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fd);
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("command not found:", 2);
		ft_putstr_fd(cmd[0], 2);
		exit(0);
	}
}

void	parent(int *end, char **argv, char **envp)
{
	char	*path;
	char	**cmd;
	int		fd;

	wait(0);
	cmd = ft_split(argv[3], ' ');
	path = search(envp, cmd[0]);
	fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("command not found:", 2);
		ft_putstr_fd(cmd[0], 2);
		exit(127);
	}
}

