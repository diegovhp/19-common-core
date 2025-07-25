/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:44 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 05:41:37 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_empty_command_args(t_command *cmd_node)
{
	if (cmd_node->args)
		return ;
	cmd_node->args = malloc(sizeof * cmd_node->args * 2);
	cmd_node->args[0] = ft_strdup(cmd_node->command);
	cmd_node->args[1] = NULL;
}

static void	configure_commands_without_arguments(t_data *data)
{
	t_command	*iterator;

	if (!data || !data->cmd)
		return ;
	iterator = data->cmd;
	while (iterator && iterator->command)
	{
		initialize_empty_command_args(iterator);
		iterator = iterator->next;
	}
}

static void	dispatch_token_processing(t_data *data, t_token **token_ptr)
{
	t_token	*token;

	token = *token_ptr;
	if (token->type == WORD || token->type == VAR)
		handle_word_tokens(&data->cmd, token_ptr);
	else if (token->type == INPUT)
		process_input_token(&data->cmd, token_ptr);
	else if (token->type == TRUNC)
		process_output_redirection(&data->cmd, token_ptr);
	else if (token->type == HEREDOC)
		handle_heredoc_redirection(data, &data->cmd, token_ptr);
	else if (token->type == APPEND)
		handle_append_redirection(&data->cmd, token_ptr);
	else if (token->type == PIPE)
		handle_pipeline_connection(&data->cmd, token_ptr);
}

void	build_command_structures(t_data *data, t_token *token)
{
	t_token	*processor;
	bool	is_first_iteration;

	processor = token;
	if (processor->type == END)
		return ;
	is_first_iteration = true;
	while (processor->next)
	{
		if (is_first_iteration)
		{
			append_command_to_list(&data->cmd, create_new_command_node(false));
			is_first_iteration = false;
		}
		if (processor->type == END)
			break ;
		dispatch_token_processing(data, &processor);
	}
	configure_commands_without_arguments(data);
}
