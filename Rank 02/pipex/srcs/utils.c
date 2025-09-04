/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:57:49 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/29 19:57:08 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_command_path(char **cmd_args, char **envp)
{
	char	*cmd;

	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
	{
		if (cmd_args)
			free_split(cmd_args);
		ft_putstr_fd("pipex: command not found: \n", 2);
		exit(127);
	}
	cmd = find_path(cmd_args[0], envp);
	if (!cmd)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd("\n", 2);
		free_split(cmd_args);
		exit(127);
	}
	return (cmd);
}

char	*join_path_cmd(char *dir, char *cmd)
{
	char	*part_path;
	char	*full_path;

	part_path = ft_strjoin(dir, "/");
	if (!part_path)
		return (NULL);
	full_path = ft_strjoin(part_path, cmd);
	free(part_path);
	return (full_path);
}

int	find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			return (i);
		i++;
	}
	return (-1);
}

void	wait_and_exit(int *fd)
{
	int		status1;
	int		status2;
	pid_t	pid1;
	pid_t	pid2;

	close(fd[0]);
	close(fd[1]);
	pid1 = wait(&status1);
	pid2 = wait(&status2);
	if (pid1 > pid2)
		exit(WEXITSTATUS(status1));
	else
		exit(WEXITSTATUS(status2));
}
