/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:46 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:16:39 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_whitespace_character(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == ' ')
			return (true);
		index++;
	}
	return (false);
}

static void	expand_variable_command_token(t_command *last_cmd, char *cmd_str)
{
	t_token	*token_list;
	t_token	*temp_token;
	char	**word_array;
	int		position;

	token_list = NULL;
	word_array = ft_split(cmd_str, ' ');
	if (!word_array)
		return ;
	last_cmd->command = ft_strdup(word_array[0]);
	if (word_array[1])
		token_list = make_token(ft_strdup(word_array[1]),
				NULL, WORD, DEFAULT);
	temp_token = token_list;
	position = 1;
	while (word_array[++position])
		add_token_to_end(&token_list,
			make_token(ft_strdup(word_array[position]),
				NULL, WORD, DEFAULT));
	add_token_to_end(&token_list,
		make_token(NULL, NULL, END, DEFAULT));
	populate_command_arguments(&token_list, last_cmd);
	free_entire_token_list(&temp_token, &cleanup_pointer);
	cleanup_string_array(word_array);
}

void	handle_word_tokens(t_command **cmd, t_token **token_lst)
{
	t_token		*current_token;
	t_command	*command_node;

	current_token = *token_lst;
	while (current_token->type == WORD || current_token->type == VAR)
	{
		command_node = get_last_command_node(*cmd);
		if (current_token->prev == NULL
			|| (current_token->prev && current_token->prev->type == PIPE)
			|| command_node->command == NULL)
		{
			if (current_token->type == VAR && has_whitespace_character
				(current_token->str))
				expand_variable_command_token(command_node, current_token->str);
			else
				command_node->command = ft_strdup(current_token->str);
			current_token = current_token->next;
		}
		else
			populate_command_arguments(&current_token, command_node);
	}
	*token_lst = current_token;
}
