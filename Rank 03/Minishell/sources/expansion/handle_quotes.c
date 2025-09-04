/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:38 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 12:29:44 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_quote_toggle(char c, int *quote_state)
{
	if ((c == '\'' || c == '\"') && *quote_state == DEFAULT)
	{
		if (c == '\'')
			*quote_state = SQUOTE;
		if (c == '\"')
			*quote_state = DQUOTE;
		return (true);
	}
	else if ((c == '\'' && *quote_state == SQUOTE)
		|| (c == '\"' && *quote_state == DQUOTE))
	{
		*quote_state = DEFAULT;
		return (true);
	}
	return (false);
}

int	unq_len(char *text, int counter, int pos)
{
	int	quote_state;

	quote_state = 0;
	while (text[pos])
	{
		if (handle_quote_toggle(text[pos], &quote_state))
		{
			pos++;
			continue ;
		}
		counter++;
		pos++;
	}
	return (counter + 1);
}

bool	has_quotation_marks(char *text)
{
	int	iterator;

	iterator = 0;
	while (text[iterator])
	{
		if (text[iterator] == '\'' || text[iterator] == '\"')
			return (true);
		iterator++;
	}
	return (false);
}

int	handle_token_quote_removal(t_data *data)
{
	t_token	*token_walker;

	token_walker = data->token;
	while (token_walker)
	{
		if (has_quotation_marks(token_walker->str) == true
			&& (!token_walker->prev || (token_walker->prev
					&& token_walker->prev->type != HEREDOC)))
			strip_quotes_from_token(&token_walker);
		token_walker = token_walker->next;
	}
	return (0);
}
