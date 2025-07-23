/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_recovery.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:46 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:17:02 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_variable_presence(t_data *data, char *variable_name)
{
	int	index;
	int	name_length;

	index = 0;
	name_length = ft_strlen(variable_name);
	while (data->env[index])
	{
		if (ft_strncmp(data->env[index], variable_name, name_length) == 0)
			return (0);
		index++;
	}
	return (1);
}

static char	*find_environment_value(t_data *data, char *variable_name)
{
	char	*result_string;
	int		env_index;
	int		name_length;

	env_index = 0;
	name_length = ft_strlen(variable_name);
	while (data->env[env_index])
	{
		if (ft_strncmp(data->env[env_index], variable_name, name_length) == 0)
			break ;
		env_index++;
	}
	result_string = ft_strdup(data->env[env_index] + name_length);
	return (result_string);
}

char	*retrieve_variable_value(t_token *token,
					char *input_string, t_data *data)
{
	char	*variable_value;
	char	*variable_name;

	variable_name = extract_variable_name(input_string);
	if (variable_name && check_variable_presence(data, variable_name) == 0)
	{
		if (token != NULL)
			token->var_exists = true;
		variable_value = find_environment_value(data, variable_name);
	}
	else if (variable_name && variable_name[0] == '?'
		&& variable_name[1] == '=')
		variable_value = ft_itoa(g_last_exit_code);
	else
		variable_value = NULL;
	cleanup_pointer(variable_name);
	return (variable_value);
}
