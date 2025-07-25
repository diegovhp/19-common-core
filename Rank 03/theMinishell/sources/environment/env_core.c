/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:12 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 14:20:53 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_reallocate_env_array(t_data *shell_data, int new_size)
{
	char	**new_env_array;
	int		env_index;

	new_env_array = ft_calloc(new_size + 1, sizeof(*new_env_array));
	if (!new_env_array)
		return (NULL);
	env_index = 0;
	while (shell_data->env[env_index] && env_index < new_size)
	{
		new_env_array[env_index] = ft_strdup(shell_data->env[env_index]);
		if (!new_env_array[env_index])
		{
			cleanup_string_array(new_env_array);
			return (NULL);
		}
		cleanup_pointer(shell_data->env[env_index]);
		env_index++;
	}
	free(shell_data->env);
	return (new_env_array);
}

char	*ft_create_env_value_string(char *value)
{
	char	*value_string;

	if (value == NULL)
		value = "";
	value_string = ft_strjoin("=", value);
	if (!value_string)
		return (NULL);
	return (value_string);
}

int	ft_find_environment_variable_index(char **environment_array,
	char *variable_name)
{
	int		search_index;
	char	*search_pattern;

	search_pattern = ft_create_search_pattern(variable_name);
	if (!search_pattern)
		return (-1);
	search_index = 0;
	while (environment_array[search_index])
	{
		if (ft_strncmp(search_pattern, environment_array[search_index],
				ft_strlen(search_pattern)) == 0)
		{
			cleanup_pointer(search_pattern);
			return (search_index);
		}
		search_index++;
	}
	cleanup_pointer(search_pattern);
	return (-1);
}

char	*ft_extract_environment_variable_value(char **environment_array,
	char *variable_name)
{
	int		search_index;
	char	*search_pattern;
	char	*variable_value;

	search_pattern = ft_create_search_pattern(variable_name);
	if (!search_pattern)
		return (NULL);
	search_index = 0;
	while (environment_array[search_index])
	{
		if (ft_strncmp(search_pattern, environment_array[search_index],
				ft_strlen(search_pattern)) == 0)
		{
			cleanup_pointer(search_pattern);
			variable_value = ft_strchr(environment_array[search_index], '=');
			if (variable_value)
				return (variable_value + 1);
			return (NULL);
		}
		search_index++;
	}
	cleanup_pointer(search_pattern);
	return (NULL);
}
