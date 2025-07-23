/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:03:42 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/21 14:29:08 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_search_pattern(char *variable_name)
{
	char	*search_pattern;

	search_pattern = ft_strjoin(variable_name, "=");
	if (!search_pattern)
		return (NULL);
	return (search_pattern);
}

static bool	ft_validate_env_key_start(char first_char)
{
	if (ft_isalpha(first_char) == 0 && first_char != '_')
		return (false);
	return (true);
}

static bool	ft_validate_env_key_chars(char *variable_name)
{
	int	char_index;

	char_index = 1;
	while (variable_name[char_index] && variable_name[char_index] != '=')
	{
		if (ft_isalnum(variable_name[char_index]) == 0
			&& variable_name[char_index] != '_')
			return (false);
		char_index++;
	}
	return (true);
}

bool	ft_validate_environment_variable_key(char *variable_name)
{
	if (!ft_validate_env_key_start(variable_name[0]))
		return (false);
	if (!ft_validate_env_key_chars(variable_name))
		return (false);
	return (true);
}

int	ft_count_environment_variables(char **environment_array)
{
	int	variable_count;

	variable_count = 0;
	while (environment_array && environment_array[variable_count])
		variable_count++;
	return (variable_count);
}
