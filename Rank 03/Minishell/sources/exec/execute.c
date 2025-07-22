/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:24 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 13:07:22 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

static int	ft_collect_child_processes(t_data *shell_data)
{
	pid_t	child_pid;
	int		process_status;
	int		final_status;

	cleanup_file_descriptors(shell_data->cmd, false);
	final_status = 0;
	child_pid = 0;
	while (child_pid != -1 || errno != ECHILD)
	{
		child_pid = waitpid(-1, &process_status, 0);
		if (child_pid == shell_data->pid)
			final_status = process_status;
	}
	if (WIFSIGNALED(final_status))
		process_status = 128 + WTERMSIG(final_status);
	else if (WIFEXITED(final_status))
		process_status = WEXITSTATUS(final_status);
	else
		process_status = final_status;
	return (process_status);
}

static int	ft_spawn_child_processes(t_data *shell_data)
{
	t_command	*current_cmd;

	current_cmd = shell_data->cmd;
	while (shell_data->pid != 0 && current_cmd)
	{
		shell_data->pid = fork();
		if (shell_data->pid == -1)
		{
			return (print_command_error("fork", NULL,
					strerror(errno), EXIT_FAILURE));
		}
		else if (shell_data->pid == 0)
			exec_cmd(shell_data, current_cmd);
		current_cmd = current_cmd->next;
	}
	return (ft_collect_child_processes(shell_data));
}

static int	ft_prepare_execution_context(t_data *shell_data)
{
	if (!shell_data || !shell_data->cmd)
		return (EXIT_SUCCESS);
	if (!shell_data->cmd->command)
	{
		if (shell_data->cmd->io_fds
			&& !validate_file_descriptors(shell_data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!initialize_command_pipes(shell_data))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

static int	ft_handle_builtin_execution(t_data *shell_data)
{
	int	builtin_result;

	if (!shell_data->cmd->pipe_output && !shell_data->cmd->prev
		&& validate_file_descriptors(shell_data->cmd->io_fds))
	{
		setup_io_redirection(shell_data->cmd->io_fds);
		builtin_result = run_builtin(shell_data, shell_data->cmd);
		reset_io_redirection(shell_data->cmd->io_fds);
		return (builtin_result);
	}
	return (CMD_NOT_FOUND);
}

int	ft_execute_command_pipeline(t_data *shell_data)
{
	int	execution_status;

	execution_status = ft_prepare_execution_context(shell_data);
	if (execution_status != CMD_NOT_FOUND)
		return (execution_status);
	execution_status = ft_handle_builtin_execution(shell_data);
	if (execution_status != CMD_NOT_FOUND)
		return (execution_status);
	return (ft_spawn_child_processes(shell_data));
}
