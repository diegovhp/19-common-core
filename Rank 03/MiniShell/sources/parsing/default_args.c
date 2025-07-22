/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:05 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 11:48:33 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**transfer_existing_to_expanded(
	int len, char **new_tab, t_command *last_cmd, t_token **tk_node)
{
	int		index;
	t_token	*current;

	index = 0;
	current = *tk_node;
	while (index < len)
	{
		new_tab[index] = last_cmd->args[index];
		index++;
	}
	while (current->type == WORD || current->type == VAR)
	{
		new_tab[index] = ft_strdup(current->str);
		index++;
		current = current->next;
	}
	new_tab[index] = NULL;
	return (new_tab);
}

int	calculate_word_tokens(t_token *temp)
{
	int	count;

	count = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	populate_command_arguments(t_token **token_node, t_command *last_cmd)
{
	if (!ft_strcmp(last_cmd->command, "echo"))
	{
		if (!(last_cmd->args))
			return (initialize_echo_arguments(token_node, last_cmd));
		else
			return (extend_echo_arguments(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->args))
			return (initialize_standard_arguments(token_node, last_cmd));
		else
			return (extend_standard_arguments(token_node, last_cmd));
	}
	return (SUCCESS);
}

int	extend_standard_arguments(t_token **token_node, t_command *last_cmd)
{
	int		new_arg_count;
	int		existing_len;
	char	**expanded_args;
	t_token	*current;

	new_arg_count = 0;
	current = *token_node;
	while (current->type == WORD || current->type == VAR)
	{
		new_arg_count++;
		current = current->next;
	}
	existing_len = 0;
	while (last_cmd->args[existing_len])
		existing_len++;
	expanded_args = malloc(sizeof(char *) * (new_arg_count + existing_len + 1));
	if (!expanded_args)
		return (FAILURE);
	expanded_args = transfer_existing_to_expanded(existing_len,
			expanded_args, last_cmd, token_node);
	free(last_cmd->args);
	last_cmd->args = expanded_args;
	*token_node = current;
	return (SUCCESS);
}

int	initialize_standard_arguments(t_token **token_node, t_command *last_cmd)
{
	int		index;
	int		total_args;
	t_token	*current;

	index = 0;
	current = *token_node;
	total_args = calculate_word_tokens(current);
	last_cmd->args = malloc(sizeof(char *) * (total_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	current = *token_node;
	index = 0;
	last_cmd->args[index] = ft_strdup(last_cmd->command);
	index++;
	while (current->type == WORD || current->type == VAR)
	{
		last_cmd->args[index] = ft_strdup(current->str);
		index++;
		current = current->next;
	}
	last_cmd->args[index] = NULL;
	*token_node = current;
	return (SUCCESS);
}
