/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:20:55 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 19:48:11 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	setup_environment_vars(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(ft_count_environment_variables(
				env) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	setup_working_directories(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->working_dir = ft_strdup(wd);
	if (!data->working_dir)
		return (false);
	if (ft_find_environment_variable_index(data->env, "OLDPWD") != -1)
	{
		data->old_working_dir = ft_strdup(
				ft_extract_environment_variable_value(data->env, "OLDPWD"));
		if (!data->old_working_dir)
			return (false);
	}
	else
	{
		data->old_working_dir = ft_strdup(wd);
		if (!data->old_working_dir)
			return (false);
	}
	return (true);
}

bool	initialize_shell_data(t_data *data, char **env)
{
	if (!setup_environment_vars(data, env))
	{
		print_command_error("Fatal", NULL,
			"Could not initialize environment", 1);
		return (false);
	}
	if (!setup_working_directories(data))
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
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_limit = NULL;
		cmd->io_fds->heredoc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_save = -1;
		cmd->io_fds->stdout_save = -1;
	}
}
