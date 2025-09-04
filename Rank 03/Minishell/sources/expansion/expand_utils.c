/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:54 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 12:57:32 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

char	*get_new_token_string(char *oldstr, char *var_value,
		int newstr_size, int index)
{
	int		pos;
	int		pos_2;
	char	*new;

	pos = 0;
	pos_2 = 0;
	new = malloc(sizeof(char) * newstr_size);
	if (!new)
		return (NULL);
	while (oldstr[pos])
	{
		if (pos == index && oldstr[pos] == '$')
		{
			copy_var_value(new, var_value, &pos_2);
			pos = pos + calculate_variable_name_length(oldstr + index) + 1;
			if (oldstr[pos] == '\0')
				break ;
		}
		new[pos_2++] = oldstr[pos++];
	}
	new[pos_2] = '\0';
	return (new);
}
