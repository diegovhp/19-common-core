/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:34 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:19:33 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_unclosed_quotes(int quote_state)
{
	if (quote_state == DQUOTE)
		print_syntax_error("unexpected EOF while looking for matching",
			"\"", true);
	else if (quote_state == SQUOTE)
		print_syntax_error("unexpected EOF while looking for matching",
			"\'", true);
	print_syntax_error("syntax error", "unexpected end of file", false);
	return (1);
}

int	parse_input_string(t_data *data, char *str)
{
	int		current_pos;
	int		string_end;
	int		token_start;
	int		quote_state;

	current_pos = -1;
	token_start = 0;
	string_end = ft_strlen(str);
	quote_state = DEFAULT;
	while (++current_pos <= string_end)
	{
		quote_state = update_quote_status(quote_state, str, current_pos);
		if (quote_state == DEFAULT)
			token_start = process_token_element(&current_pos,
					str, token_start, data);
	}
	if (quote_state != DEFAULT)
		return (handle_unclosed_quotes(quote_state));
	return (0);
}
