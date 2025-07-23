/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:10 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:18:43 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filter_empty_variable_args(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current->type == WORD || current->type == VAR)
	{
		if (current->type == VAR && current->str[0] == '\0'
			&& current->var_exists == false)
		{
			current = current->next;
			if (current == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			delete_token_node(current->prev, cleanup_pointer);
		}
		else
			current = current->next;
	}
}

char	**duplicate_args_with_expansion(int len, char **new_tab,
	t_command *last_cmd, t_token *token)
{
	int	index;

	index = 0;
	while (index < len)
	{
		new_tab[index] = last_cmd->args[index];
		index++;
	}
	while (token->type == WORD || token->type == VAR)
	{
		if (token->join == true)
			new_tab[index] = concatenate_variable_tokens(&token);
		else
			new_tab[index] = ft_strdup(token->str);
		index++;
		token = token->next;
	}
	new_tab[index] = NULL;
	return (new_tab);
}

int	calculate_expanded_args(t_token *current)
{
	int	count;

	count = 0;
	while (current && (current->type == WORD || current->type == VAR))
	{
		if (current->type == VAR && current->join == true)
		{
			while (current->type == VAR && current->join == true)
				current = current->next;
			count++;
		}
		else
		{
			count++;
			current = current->next;
		}
	}
	return (count);
}

char	*concatenate_variable_tokens(t_token **token_node)
{
	t_token	*current;
	char	*result;

	current = *token_node;
	result = ft_strdup(current->str);
	while (current->type == VAR && current->next->type == VAR
		&& current->next->join == true)
	{
		result = ft_strjoin(result, current->next->str);
		current = current->next;
	}
	*token_node = current;
	return (result);
}
