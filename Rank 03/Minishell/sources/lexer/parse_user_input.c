/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:12 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 19:12:14 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	string_contains_only_whitespace(char *input)
{
	int	position;

	position = 0;
	while (input[position])
	{
		if (!ft_isspace(input[position]))
			return (false);
		position++;
	}
	return (true);
}

bool	is_syntax_error(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (!curr)
		return (false);
	if (curr->type == PIPE)
		return (true);

	while (curr)
	{
		if (curr->type == INPUT || curr->type == TRUNC
			|| curr->type == APPEND || curr->type == HEREDOC)
		{
			if (!curr->next || curr->next->type >= PIPE)
				return (true);
		}
		curr = curr->next;
	}
	if (curr && curr->prev && curr->prev->type == PIPE)
		return (true);

	return (false);
}

static bool	validate_and_expand_tokens(t_data *data)
{
	if (validate_variable_tokens(&data->token) == FAILURE)
	{
		g_last_exit_code = SYNTAX;
		return (false);
	}
	expand_variables(data, &data->token);
	handle_token_quote_removal(data);
	return (true);
}

bool	process_command_line(t_data *data)
{
	if (data->user_input == NULL)
		builtin_exit_shell(data, NULL);
	else if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	else if (string_contains_only_whitespace(data->user_input))
		return (true);
	add_history(data->user_input);
	if (parse_input_string(data, data->user_input) == FAILURE)
	{
		g_last_exit_code = SYNTAX;
		return (false);
	}
	if (data->token->type == END)
		return (false);
	if (!validate_and_expand_tokens(data))
		return (false);
	if (is_syntax_error(data->token))
	{
		data->syntax_error = true;
		print_command_error("syntax error", NULL, NULL, SYNTAX);
		g_last_exit_code = SYNTAX;
		return (false);
	}
	build_command_structures(data, data->token);
	return (true);
}
