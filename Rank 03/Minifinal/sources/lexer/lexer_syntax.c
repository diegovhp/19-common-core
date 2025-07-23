/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:09 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:19:18 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_adjacent_operators(t_token *token_node)
{
	if (token_node->prev)
	{
		if (token_node->type == PIPE && token_node->prev->type == PIPE)
			return (true);
		if (token_node->type > PIPE && token_node->prev->type > PIPE)
			return (true);
		if (token_node->type == END && token_node->prev->type >= PIPE)
			return (true);
	}
	return (false);
}

int	verify_syntax_rules(t_token **token_lst)
{
	t_token	*current_node;

	current_node = *token_lst;
	while (current_node)
	{
		if (has_adjacent_operators(current_node) == true)
		{
			if (current_node->type == END && current_node->prev
				&& current_node->prev->type > PIPE)
				print_syntax_error("syntax error near unexpected token",
					"newline", true);
			else if (current_node->type == END && current_node->prev)
				print_syntax_error("syntax error near unexpected token",
					current_node->prev->str, true);
			else
				print_syntax_error("syntax error near unexpected token",
					current_node->str, true);
			return (FAILURE);
		}
		current_node = current_node->next;
	}
	return (SUCCESS);
}
