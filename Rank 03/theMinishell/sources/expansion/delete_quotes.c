/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:42 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 12:56:48 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_token_status_to_quoted(t_token **node_ref, int *pos_ref)
{
	if ((*node_ref)->str[*pos_ref] == '\"')
		(*node_ref)->status = DQUOTE;
	if ((*node_ref)->str[*pos_ref] == '\'')
		(*node_ref)->status = SQUOTE;
	(*pos_ref)++;
}

static bool	is_quote_character_in_default_state(t_token **node_ref, int pos)
{
	if (((*node_ref)->str[pos] == '\"' || (*node_ref)->str[pos] == '\'')
		&& (*node_ref)->status == DEFAULT)
		return (true);
	else
		return (false);
}

static bool	reset_status_to_default(t_token **node_ref, int *pos_ref)
{
	if (((*node_ref)->str[*pos_ref] == '\'' && (*node_ref)->status == SQUOTE)
		|| ((*node_ref)->str[*pos_ref] == '\"'
			&& (*node_ref)->status == DQUOTE))
	{
		(*node_ref)->status = DEFAULT;
		(*pos_ref)++;
		return (true);
	}
	else
		return (false);
}

int	strip_quotes_from_token(t_token **node_ref)
{
	int		s_pos;
	int		d_pos;
	char	*res_s;

	s_pos = 0;
	d_pos = 0;
	res_s = malloc(sizeof(char) * unq_len((*node_ref)->str, s_pos, s_pos));
	if (!res_s)
		return (1);
	while ((*node_ref)->str[s_pos])
	{
		if (reset_status_to_default(node_ref, &s_pos) == true)
			continue ;
		else if (is_quote_character_in_default_state(node_ref, s_pos) == true)
		{
			update_token_status_to_quoted(node_ref, &s_pos);
			continue ;
		}
		res_s[d_pos++] = (*node_ref)->str[s_pos++];
	}
	res_s[d_pos] = '\0';
	cleanup_pointer((*node_ref)->str);
	(*node_ref)->str = res_s;
	(*node_ref)->join = true;
	return (0);
}
