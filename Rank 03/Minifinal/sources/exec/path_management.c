/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:28 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:17:44 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_search_executable_in_paths(char *command_name,
	char **path_directories)
{
	int		path_index;
	char	*full_command_path;

	path_index = 0;
	while (path_directories[path_index])
	{
		full_command_path = ft_strjoin(path_directories[path_index],
				command_name);
		if (!full_command_path)
		{
			print_command_error("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(full_command_path, F_OK | X_OK) == 0)
			return (full_command_path);
		cleanup_pointer(full_command_path);
		path_index++;
	}
	return (NULL);
}

static char	**ft_extract_path_directories(t_data *shell_data)
{
	char	**path_array;

	if (ft_find_environment_variable_index(shell_data->env, "PATH") == -1)
		return (NULL);
	path_array = ft_split(ft_extract_environment_variable_value(
				shell_data->env, "PATH"), ':');
	if (!path_array)
		return (NULL);
	return (path_array);
}

static void	ft_cleanup_path_resources(char *command_with_slash,
	char **path_directories)
{
	if (command_with_slash)
		cleanup_pointer(command_with_slash);
	if (path_directories)
		cleanup_string_array(path_directories);
}

char	*ft_resolve_command_path(t_data *shell_data, char *command_name)
{
	char	**path_directories;
	char	*command_with_slash;
	char	*resolved_path;

	if (!command_name)
		return (NULL);
	path_directories = ft_extract_path_directories(shell_data);
	if (!path_directories)
		return (NULL);
	command_with_slash = ft_strjoin("/", command_name);
	if (!command_with_slash)
	{
		cleanup_string_array(path_directories);
		return (NULL);
	}
	resolved_path = ft_search_executable_in_paths(command_with_slash,
			path_directories);
	if (!resolved_path)
	{
		ft_cleanup_path_resources(command_with_slash, path_directories);
		return (NULL);
	}
	ft_cleanup_path_resources(command_with_slash, path_directories);
	return (resolved_path);
}
