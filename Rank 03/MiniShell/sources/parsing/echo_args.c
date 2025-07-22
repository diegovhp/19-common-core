/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:14 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 11:50:09 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extend_echo_arguments(t_token **token_node, t_command *last_cmd)
{
	int		existing_len;
	int		new_arg_count;
	char	**expanded_tab;
	t_token	*current;

	filter_empty_variable_args(token_node);
	current = *token_node;
	new_arg_count = calculate_expanded_args(current);
	existing_len = 0;
	while (last_cmd->args[existing_len])
		existing_len++;
	expanded_tab = malloc(sizeof(char *) * (new_arg_count + existing_len + 1));
	if (!expanded_tab)
		return (FAILURE);
	expanded_tab = duplicate_args_with_expansion(existing_len,
			expanded_tab, last_cmd, current);
	free(last_cmd->args);
	last_cmd->args = expanded_tab;
	while (current->type == WORD || current->type == VAR)
		current = current->next;
	*token_node = current;
	return (SUCCESS);
}

int	initialize_echo_arguments(t_token **token_node, t_command *last_cmd)
{
	int		total_args;
	t_token	*current;
	int		index;

	filter_empty_variable_args(token_node);
	current = *token_node;
	total_args = calculate_expanded_args(current);
	last_cmd->args = malloc(sizeof(char *) * (total_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	index = 0;
	last_cmd->args[index] = ft_strdup(last_cmd->command);
	index++;
	while (current->type == WORD || current->type == VAR)
	{
		if (current->join == true)
			last_cmd->args[index] = concatenate_variable_tokens(&current);
		else
			last_cmd->args[index] = ft_strdup(current->str);
		index++;
		current = current->next;
	}
	last_cmd->args[index] = NULL;
	*token_node = current;
	return (SUCCESS);
}
