/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:57:26 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/29 19:58:28 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;
	char	*cmd;
	char	**cmd_args;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		close(fd[0]);
		close(fd[1]);
		perror("pipex");
		exit(1);
	}
	close(fd[0]);
	if (dup2(filein, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(filein);
		close(fd[1]);
		exit(1);
	}
	close(filein);
	close(fd[1]);
	cmd_args = ft_split(argv[2], ' ');
	cmd = get_command_path(cmd_args, envp);
	if (execve(cmd, cmd_args, envp) == -1)
		exit(127);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;
	char	*cmd;
	char	**cmd_args;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fileout, STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		close(fileout);
		exit(1);
	}
	close(fd[0]);
	close(fileout);
	cmd_args = ft_split(argv[3], ' ');
	cmd = get_command_path(cmd_args, envp);
	if (execve(cmd, cmd_args, envp) == -1)
		exit(127);
}

void	create_pipe_and_forks(char **argv, char **envp, int *fd)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		error();
	pid1 = fork();
	if (pid1 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error();
	}
	if (pid1 == 0)
		child_process(argv, envp, fd);
	usleep(50000);
	pid2 = fork();
	if (pid2 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error();
	}
	if (pid2 == 0)
		parent_process(argv, envp, fd);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("Error: bad arguments\n", 2);
		return (1);
	}
	create_pipe_and_forks(argv, envp, fd);
	wait_and_exit(fd);
	return (0);
}
