/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:20:55 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 06:49:48 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	setup_environment_vars(t_data *data, char **env)
{
	int		env_count;
	int		current_index;
	char	**env_copy;

	env_count = ft_count_environment_variables(env);
	env_copy = ft_calloc(env_count + 1, sizeof(char *));
	if (!env_copy)
		return (false);
	data->env = env_copy;
	current_index = 0;
	while (env[current_index])
	{
		data->env[current_index] = ft_strdup(env[current_index]);
		if (!data->env[current_index])
			return (false);
		current_index++;
	}
	return (true);
}

static bool	setup_working_directories(t_data *data)
{
	char	current_dir_buffer[PATH_MAX];
	char	*current_directory;
	int		oldpwd_index;

	current_directory = getcwd(current_dir_buffer, PATH_MAX);
	data->working_dir = ft_strdup(current_directory);
	if (!data->working_dir)
		return (false);
	oldpwd_index = ft_find_environment_variable_index(data->env, "OLDPWD");
	if (oldpwd_index != -1)
	{
		data->old_working_dir = ft_strdup(
				ft_extract_environment_variable_value(data->env, "OLDPWD"));
		if (!data->old_working_dir)
			return (false);
	}
	else
	{
		data->old_working_dir = ft_strdup(current_directory);
		if (!data->old_working_dir)
			return (false);
	}
	return (true);
}

bool	initialize_shell_data(t_data *data, char **env)
{
	bool	env_success;
	bool	dir_success;

	env_success = setup_environment_vars(data, env);
	if (!env_success)
	{
		print_command_error("Fatal", NULL,
			"Could not initialize environment", 1);
		return (false);
	}
	dir_success = setup_working_directories(data);
	if (!dir_success)
	{
		print_command_error("Fatal", NULL,
			"Could not initialize working directories", 1);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	g_last_exit_code = 0;
	return (true);
}

void	setup_io_structure(t_command *cmd)
{
	t_io_fds	*new_io_fds;
	t_command	*target_cmd;

	target_cmd = cmd;
	if (!target_cmd->io_fds)
	{
		new_io_fds = malloc(sizeof(t_io_fds));
		if (!new_io_fds)
			return ;
		target_cmd->io_fds = new_io_fds;
		new_io_fds->infile = NULL;
		new_io_fds->outfile = NULL;
		new_io_fds->heredoc_limit = NULL;
		new_io_fds->heredoc_quotes = false;
		new_io_fds->fd_in = -1;
		new_io_fds->fd_out = -1;
		new_io_fds->stdin_save = -1;
		new_io_fds->stdout_save = -1;
	}
}
