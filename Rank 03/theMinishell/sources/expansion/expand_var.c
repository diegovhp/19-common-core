/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:57 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 12:57:42 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	refresh_quote_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == DEFAULT)
		(*token_node)->status = SQUOTE;
	else if (c == '\"' && (*token_node)->status == DEFAULT)
		(*token_node)->status = DQUOTE;
	else if (c == '\'' && (*token_node)->status == SQUOTE)
		(*token_node)->status = DEFAULT;
	else if (c == '\"' && (*token_node)->status == DQUOTE)
		(*token_node)->status = DEFAULT;
}

bool	check_next_separator(char c)
{
	if (c == ' ' || c == '$' || c == '\0' || c == '=')
		return (true);
	else
		return (false);
}

bool	check_var_in_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i + 1] == '\"' && str[i - 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

int	expand_variables(t_data *data, t_token **token_lst)
{
	t_token	*temp;
	int		i;

	temp = *token_lst;
	while (temp)
	{
		if (temp->type == VAR)
		{
			i = 0;
			while (temp->str[i])
			{
				refresh_quote_status(&temp, temp->str[i]);
				if (should_expand_var(temp, i))
					replace_var(&temp,
						retrieve_variable_value(temp, temp->str + i, data), i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

char	*expand_heredoc_variables(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (should_expand_heredoc_var(str, i))
			str = replace_str_heredoc(str,
					retrieve_variable_value(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}
