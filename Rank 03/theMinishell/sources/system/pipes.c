/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:54 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 06:15:59 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*allocate_pipe_descriptors(void)
{
	int	*descriptors;

	descriptors = malloc(sizeof(int) * 2);
	return (descriptors);
}

static bool	create_pipe_for_command(t_command *cmd)
{
	int	*pipe_fds;

	pipe_fds = allocate_pipe_descriptors();
	if (!pipe_fds || pipe(pipe_fds) != 0)
		return (false);
	cmd->pipe_fd = pipe_fds;
	return (true);
}

bool	configure_pipe_redirections(t_command *cmds, t_command *current_cmd)
{
	if (!current_cmd)
		return (false);
	if (current_cmd->prev && current_cmd->prev->pipe_output)
		dup2(current_cmd->prev->pipe_fd[0], STDIN_FILENO);
	if (current_cmd->pipe_output)
		dup2(current_cmd->pipe_fd[1], STDOUT_FILENO);
	cleanup_unused_pipe_fds(cmds, current_cmd);
	return (true);
}

bool	initialize_command_pipes(t_data *data)
{
	t_command	*current;

	current = data->cmd;
	while (current)
	{
		if (current->pipe_output || (current->prev
				&& current->prev->pipe_output))
		{
			if (!create_pipe_for_command(current))
			{
				cleanup_shell_data(data, false);
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}

void	cleanup_unused_pipe_fds(t_command *cmd_list, t_command *active_cmd)
{
	while (cmd_list)
	{
		if (cmd_list != active_cmd && cmd_list->pipe_fd)
		{
			close(cmd_list->pipe_fd[0]);
			close(cmd_list->pipe_fd[1]);
		}
		cmd_list = cmd_list->next;
	}
}
