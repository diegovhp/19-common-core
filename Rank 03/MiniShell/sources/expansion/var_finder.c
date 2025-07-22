/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:34 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 12:07:44 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_variable_character_validity(char character)
{
	if (ft_isalnum(character) == 0 && character != '_')
		return (false);
	else
		return (true);
}

int	calculate_variable_name_length(char *input_str)
{
	int	position;
	int	length;

	length = 0;
	position = 0;
	while (input_str[position] != '$')
		position++;
	position++;
	if ((input_str[position] >= '0' && input_str[position] <= '9')
		|| input_str[position] == '?')
		return (length + 1);
	while (input_str[position])
	{
		if (check_variable_character_validity(input_str[position]) == false)
			break ;
		length++;
		position++;
	}
	return (length);
}

char	*extract_variable_name(char *input_str)
{
	char	*variable_name;
	char	*temp_result;
	int		dollar_pos;
	int		name_length;
	int		index;

	index = 0;
	dollar_pos = 0;
	while (input_str[index])
	{
		if (input_str[index] == '$')
		{
			dollar_pos = index + 1;
			break ;
		}
		index++;
	}
	name_length = calculate_variable_name_length(input_str);
	variable_name = ft_substr(input_str, dollar_pos, name_length);
	if (!variable_name)
		return (NULL);
	temp_result = ft_strjoin(variable_name, "=");
	cleanup_pointer(variable_name);
	variable_name = temp_result;
	return (variable_name);
}
