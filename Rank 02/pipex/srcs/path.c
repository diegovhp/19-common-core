/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:58:03 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/29 19:44:26 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = join_path_cmd(paths[i], cmd);
		if (!path)
		{
			free_split(paths);
			return (NULL);
		}
		if (access(path, F_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*result;
	int		path_index;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path_index = find_path_env(envp);
	if (path_index == -1)
		return (NULL);
	paths = ft_split(envp[path_index] + 5, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	if (!result)
		free_split(paths);
	return (result);
}

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}
