/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:16 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:17:37 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	un_system_cmd(t_data *data, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND);
	if (is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = ft_resolve_command_path(data, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		print_command_error("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	run_local_cmd(t_data *data, t_command *cmd)
{
	int	ret;

	ret = check_cmd_valid(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->command, cmd->args, data->env) == -1)
		return (print_command_error("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

static void	setup_command_env(t_data *data, t_command *cmd)
{
	if (!validate_file_descriptors(cmd->io_fds))
		terminate_shell(data, EXIT_FAILURE);
	configure_pipe_redirections(data->cmd, cmd);
	setup_io_redirection(cmd->io_fds);
	cleanup_file_descriptors(data->cmd, false);
}

int	run_builtin(t_data *data, t_command *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = builtin_change_directory(data, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = builtin_echo_command(data, cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = builtin_environment_display(data, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = builtin_export_variable(data, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = builtin_print_working_directory(data, cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = builtin_remove_variable(data, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = builtin_exit_shell(data, cmd->args);
	return (ret);
}

int	exec_cmd(t_data *data, t_command *cmd)
{
	int	ret;

	if (!cmd || !cmd->command)
		terminate_shell(data, print_command_error("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	setup_command_env(data, cmd);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = run_builtin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			terminate_shell(data, ret);
		ret = un_system_cmd(data, cmd);
		if (ret != CMD_NOT_FOUND)
			terminate_shell(data, ret);
	}
	ret = run_local_cmd(data, cmd);
	terminate_shell(data, ret);
	return (ret);
}
