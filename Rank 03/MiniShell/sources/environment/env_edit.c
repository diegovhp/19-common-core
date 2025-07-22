/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:08 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 14:15:20 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_update_existing_env_var(t_data *shell_data, int var_index,
	char *key, char *value_string)
{
	cleanup_pointer(shell_data->env[var_index]);
	shell_data->env[var_index] = ft_strjoin(key, value_string);
	if (!shell_data->env[var_index])
		return (false);
	return (true);
}

static bool	ft_add_new_env_var(t_data *shell_data, char *key,
	char *value_string)
{
	int	env_count;

	env_count = ft_count_environment_variables(shell_data->env);
	shell_data->env = ft_reallocate_env_array(shell_data, env_count + 1);
	if (!shell_data->env)
		return (false);
	shell_data->env[env_count] = ft_strjoin(key, value_string);
	if (!shell_data->env[env_count])
		return (false);
	return (true);
}

bool	ft_set_environment_variable(t_data *shell_data, char *key, char *value)
{
	int		var_index;
	char	*value_string;
	bool	operation_success;

	var_index = ft_find_environment_variable_index(shell_data->env, key);
	value_string = ft_create_env_value_string(value);
	if (!value_string)
		return (false);
	if (var_index != -1 && shell_data->env[var_index])
		operation_success = ft_update_existing_env_var(shell_data, var_index,
				key, value_string);
	else
		operation_success = ft_add_new_env_var(shell_data, key, value_string);
	cleanup_pointer(value_string);
	return (operation_success);
}

bool	ft_remove_environment_variable(t_data *shell_data, int target_index)
{
	int	shift_index;
	int	final_count;

	if (target_index > ft_count_environment_variables(shell_data->env))
		return (false);
	cleanup_pointer(shell_data->env[target_index]);
	shift_index = target_index;
	final_count = target_index;
	while (shell_data->env[shift_index + 1])
	{
		shell_data->env[shift_index] = ft_strdup(
				shell_data->env[shift_index + 1]);
		if (!shell_data->env[shift_index])
			return (false);
		cleanup_pointer(shell_data->env[shift_index + 1]);
		final_count++;
		shift_index++;
	}
	shell_data->env = ft_reallocate_env_array(shell_data, final_count);
	if (!shell_data->env)
		return (false);
	return (true);
}
