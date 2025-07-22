/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:29 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 12:05:26 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	store_operator_token(t_token **token_lst, char *str, int index, int type)
{
	int		position;
	char	*operator;

	position = 0;
	if (type == APPEND || type == HEREDOC)
	{
		operator = malloc(sizeof(char) * 3);
		if (!operator)
			return (1);
		while (position < 2)
			operator[position++] = str[index++];
		operator[position] = '\0';
		add_token_to_end(token_lst, make_token(operator, NULL, type, DEFAULT));
	}
	else
	{
		operator = malloc(sizeof(char) * 2);
		if (!operator)
			return (1);
		while (position < 1)
			operator[position++] = str[index++];
		operator[position] = '\0';
		add_token_to_end(token_lst, make_token(operator, NULL, type, DEFAULT));
	}
	return (0);
}

int	extract_word_token(t_token **token_lst, char *str, int index, int start)
{
	int		position;
	char	*word_string;

	position = 0;
	word_string = malloc(sizeof(char) * (index - start + 1));
	if (!word_string)
		return (1);
	while (start < index)
	{
		word_string[position] = str[start];
		start++;
		position++;
	}
	word_string[position] = '\0';
	add_token_to_end(token_lst, \
		make_token(word_string, ft_strdup(word_string), WORD, DEFAULT));
	return (0);
}

int	identify_token_type(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}

int	update_quote_status(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		status = SQUOTE;
	else if (str[i] == '\"' && status == DEFAULT)
		status = DQUOTE;
	else if (str[i] == '\'' && status == SQUOTE)
		status = DEFAULT;
	else if (str[i] == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

int	process_token_element(int *i, char *str, int start, t_data *data)
{
	int	token_type;

	token_type = identify_token_type(str, (*i));
	if (token_type)
	{
		if ((*i) != 0 && identify_token_type(str, (*i) - 1) == 0)
			extract_word_token(&data->token, str, (*i), start);
		if (token_type == APPEND || token_type == HEREDOC || token_type == PIPE
			|| token_type == INPUT || token_type == TRUNC || token_type == END)
		{
			store_operator_token(&data->token, str, (*i), token_type);
			if (token_type == APPEND || token_type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}
