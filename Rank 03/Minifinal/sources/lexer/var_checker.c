/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:03 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:19:43 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	detect_dollar_sign_token(t_token **token_node)
{
	int	character_index;

	character_index = 0;
	while ((*token_node)->str[character_index])
	{
		if ((*token_node)->str[character_index] == '$')
		{
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break ;
			(*token_node)->type = VAR;
			return ;
		}
		character_index++;
	}
}

int	validate_variable_tokens(t_token **token_lst)
{
	t_token	*current_node;

	current_node = *token_lst;
	if (current_node->type == PIPE)
	{
		print_syntax_error("syntax error near unexpected token",
			current_node->str, true);
		return (FAILURE);
	}
	while (current_node)
	{
		detect_dollar_sign_token(&current_node);
		if (verify_syntax_rules(&current_node) == FAILURE)
			return (FAILURE);
		current_node = current_node->next;
	}
	return (SUCCESS);
}
