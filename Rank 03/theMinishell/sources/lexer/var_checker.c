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

static bool	is_heredoc_context(t_token *node)
{
	return (node->prev && node->prev->type == HEREDOC);
}

static void	mark_as_variable_if_found(t_token **token_node)
{
	char	*content;
	int		idx;

	content = (*token_node)->str;
	idx = 0;
	while (content[idx] != '\0')
	{
		if (content[idx] != '$')
		{
			idx++;
			continue ;
		}
		if (is_heredoc_context(*token_node))
			return ;
		(*token_node)->type = VAR;
		return ;
	}
}

static int	handle_initial_pipe_error(t_token *first_token)
{
	if (first_token->type != PIPE)
		return (SUCCESS);
	print_syntax_error("syntax error near unexpected token",
		first_token->str, true);
	return (FAILURE);
}

int	process_token_variables(t_token **token_lst)
{
	t_token	*walker;

	walker = *token_lst;
	if (handle_initial_pipe_error(walker) == FAILURE)
		return (FAILURE);
	while (walker != NULL)
	{
		mark_as_variable_if_found(&walker);
		if (validate_token_sequence(&walker) == FAILURE)
			return (FAILURE);
		walker = walker->next;
	}
	return (SUCCESS);
}
