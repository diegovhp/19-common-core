/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:54 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 11:44:41 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int			*file_descriptors;
	t_command	*current;

	current = data->cmd;
	while (current)
	{
		if (current->pipe_output || (current->prev
				&& current->prev->pipe_output))
		{
			file_descriptors = malloc(sizeof * file_descriptors * 2);
			if (!file_descriptors || pipe(file_descriptors) != 0)
			{
				cleanup_shell_data(data, false);
				return (false);
			}
			current->pipe_fd = file_descriptors;
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
