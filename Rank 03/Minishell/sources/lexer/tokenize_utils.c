/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:29 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 05:30:45 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// copy operator et l'ajoute a la token list
int	store_operator_token(t_token **token_lst, char *str, int index, int type)
{
	char	*operator;
	int		char_count;
	int		buffer_size;
	int		copy_idx;

	if (type == APPEND || type == HEREDOC)
		char_count = 2;
	else
		char_count = 1;
	buffer_size = char_count + 1;
	copy_idx = 0;
	operator = malloc(sizeof(char) * buffer_size);
	if (!operator)
		return (1);
	while (copy_idx < char_count)
	{
		operator[copy_idx] = str[index + copy_idx];
		copy_idx++;
	}
	operator[copy_idx] = '\0';
	add_token_to_end(token_lst, make_token(operator, NULL, type, DEFAULT));
	return (0);
}

// word into word type token
int	extract_word_token(t_token **token_lst, char *str, int index, int start)
{
	char	*word_string;
	int		word_length;
	int		copy_pos;
	int		source_pos;

	word_length = index - start;
	copy_pos = 0;
	source_pos = start;
	word_string = malloc(sizeof(char) * (word_length + 1));
	if (!word_string)
		return (1);
	while (source_pos < index)
		word_string[copy_pos++] = str[source_pos++];
	word_string[copy_pos] = '\0';
	add_token_to_end(token_lst,
		make_token(word_string, ft_strdup(word_string), WORD, DEFAULT));
	return (0);
}

// identify token type
int	identify_token_type(char *str, int i)
{
	char	current_char;

	current_char = str[i];
	if ((current_char > 8 && current_char < 14) || current_char == 32)
		return (SPACES);
	if (current_char == '|')
		return (PIPE);
	if (current_char == '<')
	{
		if (str[i + 1] == '<')
			return (HEREDOC);
		else
			return (INPUT);
	}
	if (current_char == '>')
	{
		if (str[i + 1] == '>')
			return (APPEND);
		else
			return (TRUNC);
	}
	if (current_char == '\0')
		return (END);
	return (0);
}

// default/squote/dquote, close quote
int	update_quote_status(int status, char *str, int i)
{
	char	quote_char;

	quote_char = str[i];
	if (quote_char == '\'' && status == DEFAULT)
		return (SQUOTE);
	if (quote_char == '\"' && status == DEFAULT)
		return (DQUOTE);
	if (quote_char == '\'' && status == SQUOTE)
		return (DEFAULT);
	if (quote_char == '\"' && status == DQUOTE)
		return (DEFAULT);
	return (status);
}

// create token from start to *i, store in data->token
int	process_token_element(int *i, char *str, int start, t_data *data)
{
	int	token_type;
	int	new_start;

	token_type = identify_token_type(str, *i);
	new_start = start;
	if (!token_type)
		return (start);
	if (*i != 0 && identify_token_type(str, *i - 1) == 0)
		extract_word_token(&data->token, str, *i, start);
	if (token_type == APPEND || token_type == HEREDOC || token_type == PIPE
		|| token_type == INPUT || token_type == TRUNC || token_type == END)
	{
		store_operator_token(&data->token, str, *i, token_type);
		if (token_type == APPEND || token_type == HEREDOC)
			(*i)++;
	}
	new_start = (*i) + 1;
	return (new_start);
}
