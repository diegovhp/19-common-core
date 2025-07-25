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

static bool	detect_operator_collision(t_token *node)
{
	t_token	*predecessor;

	predecessor = node->prev;
	if (!predecessor)
		return (false);
	if (node->type == PIPE && predecessor->type == PIPE)
		return (true);
	if (node->type > PIPE && predecessor->type > PIPE)
		return (true);
	if (node->type == END && predecessor->type >= PIPE)
		return (true);
	return (false);
}

static void	handle_syntax_error(t_token *node)
{
	if (node->type == END && node->prev && node->prev->type > PIPE)
		print_syntax_error("syntax error near unexpected token",
			"newline", true);
	else if (node->type == END && node->prev)
		print_syntax_error("syntax error near unexpected token",
			node->prev->str, true);
	else
		print_syntax_error("syntax error near unexpected token",
			node->str, true);
}

int	validate_token_sequence(t_token **token_lst)
{
	t_token	*iterator;

	iterator = *token_lst;
	while (iterator)
	{
		if (detect_operator_collision(iterator))
		{
			handle_syntax_error(iterator);
			return (FAILURE);
		}
		iterator = iterator->next;
	}
	return (SUCCESS);
}
