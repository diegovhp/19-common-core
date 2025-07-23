/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:34 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:18:01 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	process_chdir_failure(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	print_command_error("cd", path, strerror(errno), errno);
	return (false);
}

static void	sync_directory_variables(t_data *data, char *wd)
{
	ft_set_environment_variable(data, "OLDPWD",
		ft_extract_environment_variable_value(data->env, "PWD"));
	ft_set_environment_variable(data, "PWD", wd);
	if (data->old_working_dir)
	{
		cleanup_pointer(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		cleanup_pointer(data->working_dir);
		data->working_dir = ft_strdup(wd);
	}
	cleanup_pointer(wd);
}

static bool	execute_directory_switch(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (process_chdir_failure(path));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		print_command_error("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		ret = ft_strjoin(data->working_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		cleanup_pointer(tmp);
	}
	else
		ret = ft_strdup(cwd);
	sync_directory_variables(data, ret);
	return (true);
}

int	builtin_change_directory(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = ft_extract_environment_variable_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (print_command_error("cd", NULL,
					"HOME not set", EXIT_FAILURE));
		return (!execute_directory_switch(data, path));
	}
	if (args[2])
		return (print_command_error("cd", NULL,
				"too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = ft_extract_environment_variable_value(data->env, "OLDPWD");
		if (!path)
			return (print_command_error("cd", NULL,
					"OLDPWD not set", EXIT_FAILURE));
		return (!execute_directory_switch(data, path));
	}
	return (!execute_directory_switch(data, args[1]));
}
